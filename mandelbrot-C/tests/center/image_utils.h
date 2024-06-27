#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__
#include<stdlib.h>
#include<memory.h>
#include<stdio.h>
#include<math.h>

#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;  //specifies the file type
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file
    unsigned short bfReserved1;  //reserved; must be 0
    unsigned short bfReserved2;  //reserved; must be 0
    unsigned int bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct
    int biWidth;  //specifies width in pixels
    int biHeight;  //specifies height in pixels
    unsigned short biPlanes;  //specifies the number of color planes, must be 1
    unsigned short biBitCount;  //specifies the number of bits per pixel
    unsigned int biCompression;  //specifies the type of compression
    unsigned int biSizeImage;  //size of image in bytes
    int biXPelsPerMeter;  //number of pixels per meter in x axis
    int biYPelsPerMeter;  //number of pixels per meter in y axis
    unsigned int biClrUsed;  //number of colors used by the bitmap
    unsigned int biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

typedef struct tagCOLORTABLE {
    unsigned char r,g,b,junk;
} COLORINDEX;

typedef struct tagBitmapImageHeader {
    BITMAPFILEHEADER bmFileHeader;
    BITMAPINFOHEADER bmInfoHeader;
    COLORINDEX colorIdx[256];
} BitmapImageHeader;

typedef struct tagBitMapFile {
    BitmapImageHeader bmHeader;
    unsigned char * bmData;
} BitMapFile;

#pragma pack(pop)

void color_table(BitMapFile* pbmFile);
void InitImage(BitMapFile* pbmFile, int height, int width)
{
    unsigned int headerSize = 
        sizeof(BITMAPFILEHEADER) + 
        sizeof(BITMAPINFOHEADER) + 
        sizeof(COLORINDEX) * 255;
    COLORINDEX pColorIndex[255];
    memset(pbmFile, 0, sizeof(BitMapFile));
    pbmFile->bmHeader.bmInfoHeader.biWidth = width;
    pbmFile->bmHeader.bmInfoHeader.biHeight = height;
    pbmFile->bmHeader.bmFileHeader.bfType =  (((unsigned short)'M') << 8) | 'B';
    pbmFile->bmHeader.bmFileHeader.bfSize = headerSize + width * height;
    pbmFile->bmHeader.bmFileHeader.bfOffBits = headerSize;
    pbmFile->bmHeader.bmInfoHeader.biBitCount = 8;
    pbmFile->bmHeader.bmInfoHeader.biSize = 40;
    pbmFile->bmHeader.bmInfoHeader.biPlanes = 1;
    pbmFile->bmHeader.bmInfoHeader.biSizeImage = width * height;
    pbmFile->bmData = (unsigned char*) malloc(width * height);


    pbmFile->bmHeader.bmInfoHeader.biClrUsed = 180;
    pbmFile->bmHeader.bmInfoHeader.biClrImportant = 180;
}

void WriteBitmapFile(int fileNumber, BitMapFile* pbmFile)
{
    char filename[255];
    sprintf(filename, "%05d.bmp", fileNumber);
     FILE *filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
    {
        printf("Error opening file for write.");
        return;
    }        

    fwrite(& pbmFile->bmHeader, sizeof(BitmapImageHeader), 1, filePtr);
    fwrite( pbmFile->bmData, pbmFile->bmHeader.bmInfoHeader.biSizeImage, 1, filePtr);
    fclose(filePtr);
}

void color_table(BitMapFile* pbmFile)
{
    double x;
    // for ( int i=2; i<360; i+=2)
    // {
    //     x=1.0 - fabs(fmod(((i+0.0)/60.0),2)-1.0);
    //     if (i>=0 && i<60)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].r=255;
    //         pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
    //         pbmFile->bmHeader.colorIdx[i].b=0;
        
    //     }
    //     if (i>=60 && i<120)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);
    //         pbmFile->bmHeader.colorIdx[i].g=255;
    //         pbmFile->bmHeader.colorIdx[i].b=0;
        
    //     }
    //     if (i>=120 && i<180)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].r=0;
    //         pbmFile->bmHeader.colorIdx[i].g=255;
    //         pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
        
    //     }
    //    if (i>=180 && i<240)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].r=0;
    //         pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
    //         pbmFile->bmHeader.colorIdx[i].b=255;
    //     }
    //     if (i>=240 && i<300)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].g=0;
    //         pbmFile->bmHeader.colorIdx[i].b=255;
    //         pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);

        
    //     }
    //     if (i>=300 && i<360)
    //     {
    //         pbmFile->bmHeader.colorIdx[i].g=0;
    //         pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
    //         pbmFile->bmHeader.colorIdx[i].r=255;
    //     }                
    // }
        for ( int i=1; i<=180; i++)
    {
        x=1.0 - fabs(fmod(((i+0.0)/30.0),2)-1.0);
        if (i>=0 && i<30)
        {
            pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].b=0;
        
        }
        if (i>=30 && i<60)
        {
            pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].b=0;
        
        }
        if (i>=60 && i<90)
        {
            pbmFile->bmHeader.colorIdx[i].r=0;
            pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
        
        }
       if (i>=90 && i<120)
        {
            pbmFile->bmHeader.colorIdx[i].r=0;
            pbmFile->bmHeader.colorIdx[i].g=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
        }
        if (i>=120 && i<150)
        {
            pbmFile->bmHeader.colorIdx[i].g=0;
            pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);

        
        }
        if (i>=150 && i<180)
        {
            pbmFile->bmHeader.colorIdx[i].g=0;
            pbmFile->bmHeader.colorIdx[i].b=(int)(x*255);
            pbmFile->bmHeader.colorIdx[i].r=(int)(x*255);
        }        
    }    
}

#endif