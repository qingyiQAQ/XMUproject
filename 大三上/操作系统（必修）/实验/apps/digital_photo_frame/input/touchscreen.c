#include <config.h>
#include <input_manager.h>
#include <disp_manager.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

//#include <tslib.h>
//#include <draw.h>

enum TouchIoctlCmd {
    INPUT_IOCTL_GET_EVENT_DATA,
    INPUT_IOCTL_SET_POWER_STATUS,
    INPUT_IOCTL_GET_POWER_STATUS,
    INPUT_IOCTL_GET_DEVICE_TYPE,
    INPUT_IOCTL_GET_CHIP_INFO,
    INPUT_IOCTL_GET_VENDOR_NAME,
    INPUT_IOCTL_GET_CHIP_NAME,
    INPUT_IOCTL_SET_GESTURE_MODE,
    INPUT_IOCTL_RUN_CAPACITANCE_TEST,
    INPUT_IOCTL_RUN_EXTRA_CMD,
};

/**
 * @brief Describes the input event data.
 */
typedef struct {
    int x;                   /**< X coordinate of a touch point */
    int y;                   /**< Y coordinate of a touch point */
    int pressure;            /**< Z coordinate of a touch point, such as the pressure */
    int definedEvent;        /**< Specific input event, such as the pick-up or put-down event */
    unsigned int fingerID;           /**< Finger ID, used in multi-touch scenarios */
    unsigned int pointNum;           /**< Total number of fingers touching the screen */
    struct timeval timeStamp;    /**< Timestamp */
    char moreDataFlag;           /**< Flag of continuous data read */
} InputEventData;


//static struct tsdev *g_tTSDev;
static int giInputFd = -1;

/**********************************************************************
 * �������ƣ� TouchScreenDevInit
 * ���������� ����������ģ����豸��ʼ������
 *            ע��: ����Ҫ�õ�LCD�ķֱ���, �˺���Ҫ��SelectAndInitDisplay֮����ܵ��� 
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
static int TouchScreenDevInit(void)
{
#if 0
	if ((pcTSName = getenv("TSLIB_TSDEVICE")) != NULL ) 
	{
		g_tTSDev = ts_open(pcTSName, 0);  /* ��������ʽ�� */
	}
	else
	{
		g_tTSDev = ts_open("/dev/event0", 1);
	}

	if (!g_tTSDev) {
		DBG_PRINTF(APP_ERR"ts_open error!\n");
		return -1;
	}

	if (ts_config(g_tTSDev)) {
		DBG_PRINTF("ts_config error!\n");
		return -1;
	}
#else
	giInputFd = open("/dev/input/event1", O_RDWR);
	if (giInputFd< 0)
	{
		printf("can not open /dev/input/event1\n");
		return -1;
	}
#endif
	return 0;
}

/**********************************************************************
 * �������ƣ� StdinDevExit
 * ���������� ����������ģ����豸�˳�����
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
static int TouchScreenDevExit(void)
{
	close(giInputFd);
	return 0;
}


/**********************************************************************
 * �������ƣ� TouchScreenGetInputEvent
 * ���������� ����������ģ��Ķ�ȡ���ݺ���,���ڴ���������ģ������߳��б�����
 * ��������� ��
 * ��������� ptInputEvent - �ں��õ�����������
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
static int TouchScreenGetInputEvent(PT_InputEvent ptInputEvent)
{
	//struct ts_sample tSamp;
	int iRet;	
	InputEventData eventData;
	struct pollfd fds[1];
	nfds_t nfds = 1;
	static int x, y;

	while (1)
	{

		fds[0].fd = giInputFd;
		fds[0].events = POLLIN;
		fds[0].revents = 0;
 
 		iRet = poll(fds, nfds, -1); /* ��������������� */
		if (iRet == 1 && fds[0].revents == POLLIN)
		{
			ioctl(giInputFd, INPUT_IOCTL_GET_EVENT_DATA, &eventData);
			//printf("get event: x = %d, y = %d, pressure = %d\n", eventData.x, eventData.y, eventData.pressure);
			//ptInputEvent->tTime     = tSamp.tv;
			ptInputEvent->iType     = INPUT_TYPE_TOUCHSCREEN;
			ptInputEvent->iX        = eventData.x;
			ptInputEvent->iY        = eventData.y;
			ptInputEvent->iPressure = eventData.pressure;

			if (ptInputEvent->iPressure == 0)
			{
				ptInputEvent->iX = x;
				ptInputEvent->iY = y;				
			}

			x = eventData.x;
			y = eventData.y;
			
			return 0;

		}
		else
		{
			return -1;
		}
	}

	return 0;
}


static T_InputOpr g_tTouchScreenOpr = {
	.name          = "touchscreen",
	.DeviceInit    = TouchScreenDevInit,
	.DeviceExit    = TouchScreenDevExit,
	.GetInputEvent = TouchScreenGetInputEvent,
};

/**********************************************************************
 * �������ƣ� TouchScreenInit
 * ���������� ע��"����������ģ��"
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int TouchScreenInit(void)
{
	return RegisterInputOpr(&g_tTouchScreenOpr);
}

