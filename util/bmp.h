
#ifndef CHENLEECV_H
#define CHENLEECV_H
 #include "mongoose.h"

typedef struct
{
	//unsigned short    bfType;
	uint32_t   bfSize;
	uint16_t    bfReserved1;
	uint16_t    bfReserved2;
	uint32_t   bfOffBits;
} ClBitMapFileHeader;
 
typedef struct
{
	uint32_t biSize; 
	uint32_t   biWidth; 
	uint32_t   biHeight; 
	uint16_t   biPlanes; 
	uint16_t   biBitCount;
	uint32_t   biCompression; 
	uint32_t   biSizeImage; 
	uint32_t    biXPelsPerMeter; 
	uint32_t    biYPelsPerMeter; 
	uint32_t    biClrUsed; 
	uint32_t    biClrImportant; 
} ClBitMapInfoHeader;
 
typedef struct 
{
	uint8_t rgbBlue; //����ɫ����ɫ����
	uint8_t rgbGreen; //����ɫ����ɫ����
	uint8_t rgbRed; //����ɫ�ĺ�ɫ����
	uint8_t rgbReserved; //����ֵ
} ClRgbQuad;
 
typedef struct
{
	int32_t width;
	int32_t height;
	int32_t channels;
	int8_t* imageData;
}ClImage;
 
ClImage* clLoadImage(char* path);
bool clSaveImage(char* path, ClImage* bmpImg);
 

#endif