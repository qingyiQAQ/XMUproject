#include <config.h>
#include <pic_operation.h>
#include <picfmt_manager.h>
#include <file.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push) /* ����ǰpack����ѹջ���� */
#pragma pack(1)    /* �����ڽṹ�嶨��֮ǰʹ��,����Ϊ���ýṹ���и���Ա��1�ֽڶ��� */

typedef struct tagBITMAPFILEHEADER { /* bmfh */
	unsigned short bfType; 
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER { /* bmih */
	unsigned long  biSize;
	unsigned long  biWidth;
	unsigned long  biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	unsigned long  biXPelsPerMeter;
	unsigned long  biYPelsPerMeter;
	unsigned long  biClrUsed;
	unsigned long  biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop) /* �ָ���ǰ��pack���� */

static int isBMPFormat(PT_FileMap ptFileMap);
static int GetPixelDatasFrmBMP(PT_FileMap ptFileMap, PT_PixelDatas ptPixelDatas);
static int FreePixelDatasForBMP(PT_PixelDatas ptPixelDatas);

static T_PicFileParser g_tBMPParser = {
	.name           = "bmp",
	.isSupport      = isBMPFormat,
	.GetPixelDatas  = GetPixelDatasFrmBMP,
	.FreePixelDatas = FreePixelDatasForBMP,	
};

/**********************************************************************
 * �������ƣ� isBMPFormat
 * ���������� BMPģ���Ƿ�֧�ָ��ļ�,�����ļ��Ƿ�ΪBMP�ļ�
 * ��������� ptFileMap - �ں��ļ���Ϣ
 * ��������� ��
 * �� �� ֵ�� 0 - ��֧��, 1 - ֧��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
static int isBMPFormat(PT_FileMap ptFileMap)
{
    unsigned char *aFileHead = ptFileMap->pucFileMapMem;
    
	if (aFileHead[0] != 0x42 || aFileHead[1] != 0x4d)
		return 0;
	else
		return 1;
}

/**********************************************************************
 * �������ƣ� CovertOneLine
 * ���������� ��BMP�ļ���һ�е���������,ת��Ϊ������ʾ�豸��ʹ�õĸ�ʽ
 * ��������� iWidth      - ���,�����ٸ�����
 *            iSrcBpp     - BMP�ļ���һ�������ö���λ����ʾ
 *            iDstBpp     - ��ʾ�豸��һ�������ö���λ����ʾ
 *            pudSrcDatas - BMP�ļ���������ݵ�λ��
 *            pudDstDatas - ת���������ݴ洢��λ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
static int CovertOneLine(int iWidth, int iSrcBpp, int iDstBpp, unsigned char *pudSrcDatas, unsigned char *pudDstDatas)
{
	unsigned int dwRed;
	unsigned int dwGreen;
	unsigned int dwBlue;
	unsigned int dwColor;

	unsigned short *pwDstDatas16bpp = (unsigned short *)pudDstDatas;
	unsigned int   *pwDstDatas32bpp = (unsigned int *)pudDstDatas;

	int i;
	int pos = 0;

	if (iSrcBpp != 24)
	{
		return -1;
	}

	if (iDstBpp == 24)
	{
		memcpy(pudDstDatas, pudSrcDatas, iWidth*3);
	}
	else
	{
		for (i = 0; i < iWidth; i++)
		{
			dwBlue  = pudSrcDatas[pos++];
			dwGreen = pudSrcDatas[pos++];
			dwRed   = pudSrcDatas[pos++];
			if (iDstBpp == 32)
			{
				dwColor = (dwRed << 16) | (dwGreen << 8) | dwBlue;
				*pwDstDatas32bpp = dwColor;
				pwDstDatas32bpp++;
			}
			else if (iDstBpp == 16)
			{
				/* 565 */
				dwRed   = dwRed >> 3;
				dwGreen = dwGreen >> 2;
				dwBlue  = dwBlue >> 3;
				dwColor = (dwRed << 11) | (dwGreen << 5) | (dwBlue);
				*pwDstDatas16bpp = dwColor;
				pwDstDatas16bpp++;
			}
		}
	}
	return 0;
}

/**********************************************************************
 * �������ƣ� GetPixelDatasFrmBMP
 * ���������� ��BMP�ļ��е���������,ȡ����ת��Ϊ������ʾ�豸��ʹ�õĸ�ʽ
 * ��������� ptFileMap    - �ں��ļ���Ϣ
 * ��������� ptPixelDatas - �ں���������
 *            ptPixelDatas->iBpp ������Ĳ���, ��ȷ����BMP�ļ��õ�������Ҫת��Ϊ��BPP
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���          �޸�����
 * -----------------------------------------------
 * 2013/02/08        V1.0     Τ��ɽ          ����
 ***********************************************************************/
static int GetPixelDatasFrmBMP(PT_FileMap ptFileMap, PT_PixelDatas ptPixelDatas)
{
	BITMAPFILEHEADER *ptBITMAPFILEHEADER;
	//BITMAPINFOHEADER *ptBITMAPINFOHEADER;
	BITMAPINFOHEADER mapInfo;
	BITMAPFILEHEADER headInfo;

    unsigned char *aFileHead;
	int i;

	int iWidth;
	int iHeight;
	int iBMPBpp;
	int y;

	unsigned char *pucSrc;
	unsigned char *pucDest;
	int iLineWidthAlign;
	int iLineWidthReal;
	char *dest;
	char *src;

    aFileHead = ptFileMap->pucFileMapMem;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)aFileHead;
	//ptBITMAPINFOHEADER = (BITMAPINFOHEADER *)(aFileHead + sizeof(BITMAPFILEHEADER));
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	//memcpy(&mapInfo, aFileHead + sizeof(BITMAPFILEHEADER), sizeof(mapInfo));
	dest = &mapInfo;
	src  = (aFileHead + sizeof(BITMAPFILEHEADER));
	for (i = 0; i < sizeof(mapInfo); i++)
		dest[i] = src[i];

	dest = &headInfo;
	src  = ptBITMAPFILEHEADER;
	for (i = 0; i < sizeof(headInfo); i++)
		dest[i] = src[i];

	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	iWidth = mapInfo.biWidth;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iHeight = mapInfo.biHeight;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iBMPBpp = mapInfo.biBitCount;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	if (iBMPBpp != 24)
	{
		DBG_PRINTF("iBMPBpp = %d\n", iBMPBpp);
		DBG_PRINTF("sizeof(BITMAPFILEHEADER) = %d\n", sizeof(BITMAPFILEHEADER));
		return -1;
	}

	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->iWidth  = iWidth;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->iHeight = iHeight;
	//ptPixelDatas->iBpp    = iBpp;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->iLineBytes    = iWidth * ptPixelDatas->iBpp / 8;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    ptPixelDatas->iTotalBytes   = ptPixelDatas->iHeight * ptPixelDatas->iLineBytes;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->aucPixelDatas = malloc(ptPixelDatas->iTotalBytes);
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	if (NULL == ptPixelDatas->aucPixelDatas)
	{
		return -1;
	}

	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iLineWidthReal = iWidth * iBMPBpp / 8;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iLineWidthAlign = (iLineWidthReal + 3) & ~0x3;   /* ��4ȡ�� */
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
		
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	pucSrc = aFileHead + headInfo.bfOffBits;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	pucSrc = pucSrc + (iHeight - 1) * iLineWidthAlign;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	pucDest = ptPixelDatas->aucPixelDatas;
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	
	for (y = 0; y < iHeight; y++)
	{		
		//memcpy(pucDest, pucSrc, iLineWidthReal);
		CovertOneLine(iWidth, iBMPBpp, ptPixelDatas->iBpp, pucSrc, pucDest);
		pucSrc  -= iLineWidthAlign;
		pucDest += ptPixelDatas->iLineBytes;
	}
	printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;	
}

/**********************************************************************
 * �������ƣ� FreePixelDatasForBMP
 * ���������� GetPixelDatasFrmBMP�ķ�����,������������ռ�ڴ��ͷŵ�
 * ��������� ptPixelDatas - �ں���������
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���          �޸�����
 * -----------------------------------------------
 * 2013/02/08        V1.0     Τ��ɽ          ����
 ***********************************************************************/
static int FreePixelDatasForBMP(PT_PixelDatas ptPixelDatas)
{
	free(ptPixelDatas->aucPixelDatas);
	return 0;
}

/**********************************************************************
 * �������ƣ� BMPParserInit
 * ���������� ע��"BMP�ļ�����ģ��"
 * ��������� ��
 * ��������� ��
 * �� �� ֵ�� 0 - �ɹ�, ����ֵ - ʧ��
 * �޸�����        �汾��     �޸���	      �޸�����
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  Τ��ɽ	      ����
 ***********************************************************************/
int BMPParserInit(void)
{
	return RegisterPicFileParser(&g_tBMPParser);
}

