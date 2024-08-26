#include <config.h>
#include <pic_operation.h>
#include <picfmt_manager.h>
#include <file.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push) /* 将当前pack设置压栈保存 */
#pragma pack(1)    /* 必须在结构体定义之前使用,这是为了让结构体中各成员按1字节对齐 */

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

#pragma pack(pop) /* 恢复先前的pack设置 */

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
 * 函数名称： isBMPFormat
 * 功能描述： BMP模块是否支持该文件,即该文件是否为BMP文件
 * 输入参数： ptFileMap - 内含文件信息
 * 输出参数： 无
 * 返 回 值： 0 - 不支持, 1 - 支持
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
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
 * 函数名称： CovertOneLine
 * 功能描述： 把BMP文件中一行的象素数据,转换为能在显示设备上使用的格式
 * 输入参数： iWidth      - 宽度,即多少个象素
 *            iSrcBpp     - BMP文件中一个象素用多少位来表示
 *            iDstBpp     - 显示设备上一个象素用多少位来表示
 *            pudSrcDatas - BMP文件里该行数据的位置
 *            pudDstDatas - 转换所得数据存储的位置
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
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
				/* 555 */
				dwRed   = dwRed >> 3;
				dwGreen = dwGreen >> 3;
				dwBlue  = dwBlue >> 3;
				dwColor = (dwRed << 10) | (dwGreen << 5) | (dwBlue);
				*pwDstDatas16bpp = (unsigned short)dwColor;

				pwDstDatas16bpp++;

			}
		}
	}

	return 0;
}

/**********************************************************************
 * 函数名称： GetPixelDatasFrmBMP
 * 功能描述： 把BMP文件中的象素数据,取出并转换为能在显示设备上使用的格式
 * 输入参数： ptFileMap    - 内含文件信息
 * 输出参数： ptPixelDatas - 内含象素数据
 *            ptPixelDatas->iBpp 是输入的参数, 它确定从BMP文件得到的数据要转换为该BPP
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人          修改内容
 * -----------------------------------------------
 * 2013/02/08        V1.0     韦东山          创建
 ***********************************************************************/
static int GetPixelDatasFrmBMP(PT_FileMap ptFileMap, PT_PixelDatas ptPixelDatas)
{
	BITMAPFILEHEADER *ptBITMAPFILEHEADER;
	BITMAPINFOHEADER *ptBITMAPINFOHEADER;
	BITMAPINFOHEADER mapInfo;
	BITMAPINFOHEADER mapInfoHead;
	unsigned long  bfOffBits;

    unsigned char *aFileHead;

	int iWidth;
	int iHeight;
	int iBMPBpp;
	int y;

	unsigned char *pucSrc;
	unsigned char *pucDest;
	int iLineWidthAlign;
	int iLineWidthReal;
	unsigned short *wfb;

	int i;

	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	aFileHead = ptFileMap->pucFileMapMem;

	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptBITMAPFILEHEADER = (BITMAPFILEHEADER *)aFileHead;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptBITMAPINFOHEADER = (BITMAPINFOHEADER *)(aFileHead + sizeof(BITMAPFILEHEADER));

	pucDest = &mapInfo;
	pucSrc  = (aFileHead + sizeof(BITMAPFILEHEADER));
	for (i = 0; i < sizeof(mapInfo); i++)
		pucDest[i] = pucSrc[i];

	pucDest = &mapInfoHead;
	pucSrc  = ptBITMAPINFOHEADER;
	for (i = 0; i < sizeof(mapInfoHead); i++)
		pucDest[i] = pucSrc[i];

	pucDest = &bfOffBits;
	pucSrc  = &ptBITMAPFILEHEADER->bfOffBits;
	for (i = 0; i < sizeof(bfOffBits); i++)
		pucDest[i] = pucSrc[i];


	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iWidth = mapInfo.biWidth;                     // Alignment fault
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iHeight = mapInfoHead.biHeight;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iBMPBpp = mapInfoHead.biBitCount;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	if (iBMPBpp != 24)
	{
		DBG_PRINTF("iBMPBpp = %d\n", iBMPBpp);
		DBG_PRINTF("sizeof(BITMAPFILEHEADER) = %d\n", sizeof(BITMAPFILEHEADER));
		return -1;
	}

	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->iWidth  = iWidth;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->iHeight = iHeight;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	//ptPixelDatas->iBpp    = iBpp;
	ptPixelDatas->iLineBytes    = iWidth * ptPixelDatas->iBpp / 8;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    ptPixelDatas->iTotalBytes   = ptPixelDatas->iHeight * ptPixelDatas->iLineBytes;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	ptPixelDatas->aucPixelDatas = malloc(ptPixelDatas->iTotalBytes);
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	if (NULL == ptPixelDatas->aucPixelDatas)
	{
		return -1;
	}

	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iLineWidthReal = iWidth * iBMPBpp / 8;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iLineWidthAlign = (iLineWidthReal + 3) & ~0x3;   /* 向4取整 */

	pucSrc = aFileHead + bfOffBits;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	pucSrc = pucSrc + (iHeight - 1) * iLineWidthAlign;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	pucDest = ptPixelDatas->aucPixelDatas;
	//printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	for (y = 0; y < iHeight; y++)
	{		
		//memcpy(pucDest, pucSrc, iLineWidthReal);
		CovertOneLine(iWidth, iBMPBpp, ptPixelDatas->iBpp, pucSrc, pucDest);
		pucSrc  -= iLineWidthAlign;
		pucDest += ptPixelDatas->iLineBytes;
	}
	
	return 0;	
}

/**********************************************************************
 * 函数名称： FreePixelDatasForBMP
 * 功能描述： GetPixelDatasFrmBMP的反函数,把象素数据所占内存释放掉
 * 输入参数： ptPixelDatas - 内含象素数据
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人          修改内容
 * -----------------------------------------------
 * 2013/02/08        V1.0     韦东山          创建
 ***********************************************************************/
static int FreePixelDatasForBMP(PT_PixelDatas ptPixelDatas)
{
	free(ptPixelDatas->aucPixelDatas);
	return 0;
}

/**********************************************************************
 * 函数名称： BMPParserInit
 * 功能描述： 注册"BMP文件解析模块"
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 0 - 成功, 其他值 - 失败
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2013/02/08	     V1.0	  韦东山	      创建
 ***********************************************************************/
int BMPParserInit(void)
{
	return RegisterPicFileParser(&g_tBMPParser);
}

