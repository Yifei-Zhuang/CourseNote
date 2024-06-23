//
// Created by 庄毅非 on 2021/10/26.
//

//
// Created by 庄毅非 on 2021/10/25.
//

#ifndef DIP_HW1_DIP_H
#define DIP_HW1_DIP_H
// #define DEBUG
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isRGBEmpty = 1;
int isYUVEmpty = 1;
typedef struct unit
{
    int w;
    int h;
    double weight;
} Unit;
struct OperationType
{
    int gray;
    int red;
    int green;
    int blue;
};
typedef struct headBMPFile
{
    uint32_t size;
    uint16_t reserved1, reserved2;
    uint32_t offset;
    void (*readBmpHead)(struct headBMPFile *bmpHead, FILE *, int);
    void (*writeBmpHead)(struct headBMPFile *bmpHead, FILE *);
} bmpHeadStruct;

typedef struct headDIB
{
    int32_t width, height;
    uint16_t plane, bits_per_pixel;
    uint32_t compression, imageSize;
    int32_t pixels_per_x, pixels_per_y;
    uint32_t colors, importantColors;
    void (*readDibHead)(struct headDIB *, FILE *, int);
    void (*writeDibHead)(struct headDIB *, FILE *);
} dibHeadStruct;

struct RGB
{
    uint8_t b, g, r;
};
struct YUV
{
    double y, u, v;
};
enum COLORSPACE
{
    RGB,
    YUV
};
typedef struct BitMap
{
    enum COLORSPACE colorSpace;
    struct RGB **rgbTable;
    struct YUV **yuvTable;
    uint32_t width, height;
    void (*changeSize)(struct BitMap *, uint32_t, uint32_t);
} bitMapStruct;
struct RGB **newRGBTable;
struct YUV **newYUVTable;

struct BMP
{
    bmpHeadStruct bmpHead;
    dibHeadStruct dibHead;
    bitMapStruct bitMap;
    void (*read)(struct BMP *, const char fileName[]);
    void (*write)(struct BMP *, const char fileName[]);
    void (*rgbToYUV)(struct BMP *);
    void (*yuvToRGB)(struct BMP *);
    void (*toGrayScale)(struct BMP *);
    void (*meanFilter)(struct BMP *, struct OperationType);
    void (*laplaceTrans)(struct BMP *, struct OperationType);
    void (*laplaceEnhance)(struct BMP *, struct OperationType, double rate);
};

// offset应该设置默认值为0
void readBMPHead_f(bmpHeadStruct *bmpHead, FILE *file, int offset)
{
    fseek(file, offset, SEEK_SET);
    short type = 0;
    fread(&type, sizeof(char), 2, file);
    if (type != 0x4D42)
    {
        fprintf(stderr, "this file is not bmp file");
        exit(1);
    }
    fread(&bmpHead->size, 4, 1, file);
    fread(&bmpHead->reserved1, 2, 1, file);
    fread(&bmpHead->reserved2, 2, 1, file);
    fread(&bmpHead->offset, 4, 1, file);
}

void writeBmpHead_f(struct headBMPFile *bmpHead, FILE *outputFile)
{
    uint8_t fileType[2] = {0x42, 0x4D};
    fwrite((char *)fileType, sizeof(uint8_t), 2, outputFile);
    fwrite(&bmpHead->size, 4, 1, outputFile);
    fwrite(&bmpHead->reserved1, 2, 1, outputFile);
    fwrite(&bmpHead->reserved2, 2, 1, outputFile);
    fwrite(&bmpHead->offset, 4, 1, outputFile);
}

// DIB

void readDibHead_f(struct headDIB *dibHead, FILE *inputFile, int offset)
{
    uint32_t headSize = 0;
    fread(&headSize, 4, 1, inputFile);
    if (headSize != 40)
    {
        fprintf(stderr, "cannot read bmp file whose offset is bigger than 54");
        exit(1);
    }
    fread(&dibHead->width, 4, 1, inputFile);
    fread(&dibHead->height, 4, 1, inputFile);
    fread(&dibHead->plane, 2, 1, inputFile);
    fread(&dibHead->bits_per_pixel, 2, 1, inputFile);
    fread(&dibHead->compression, 4, 1, inputFile);
    fread(&dibHead->imageSize, 4, 1, inputFile);
    fread(&dibHead->pixels_per_x, 4, 1, inputFile);
    fread(&dibHead->pixels_per_y, 4, 1, inputFile);
    fread(&dibHead->colors, 4, 1, inputFile);
    fread(&dibHead->importantColors, 4, 1, inputFile);
}
void writeDibHead_f(struct headDIB *dibHead, FILE *outputFile)
{
    uint32_t headSize = 40;
    fwrite(&headSize, 4, 1, outputFile);
    fwrite(&dibHead->width, 4, 1, outputFile);
    fwrite(&dibHead->height, 4, 1, outputFile);
    fwrite(&dibHead->plane, 2, 1, outputFile);
    fwrite(&dibHead->bits_per_pixel, 2, 1, outputFile);
    fwrite(&dibHead->compression, 4, 1, outputFile);
    fwrite(&dibHead->imageSize, 4, 1, outputFile);
    fwrite(&dibHead->pixels_per_x, 4, 1, outputFile);
    fwrite(&dibHead->pixels_per_y, 4, 1, outputFile);
    fwrite(&dibHead->colors, 4, 1, outputFile);
    fwrite(&dibHead->importantColors, 4, 1, outputFile);
}

// BitMap
void changeSize_f(struct BitMap *bitMap, uint32_t height, uint32_t width)
{
    if (!bitMap)
        return;
    if (bitMap->colorSpace == RGB)
    {
        newRGBTable = (struct RGB **)malloc(height * sizeof(struct RGB *));
        for (int i = 0; i < height; i++)
        {
            newRGBTable[i] = (struct RGB *)malloc(width * sizeof(struct RGB));
        }
        if (isRGBEmpty == 1)
        {
            bitMap->rgbTable = newRGBTable;
            isRGBEmpty = 0;
            return;
        }
        uint32_t minWidth = width < bitMap->width ? width : bitMap->width;
        uint32_t minHeight = height < bitMap->height ? height : bitMap->height;
        for (uint32_t i = 0; i < minHeight; i++)
        {
            for (int j = 0; j < minWidth; j++)
            {
                newRGBTable[i][j].r = bitMap->rgbTable[i][j].r;
                newRGBTable[i][j].g = bitMap->rgbTable[i][j].g;
                newRGBTable[i][j].b = bitMap->rgbTable[i][j].b;
            }
        }

        for (int i = 0; i < bitMap->height; i++)
        {
            free(bitMap->rgbTable[i]);
        }
        free(bitMap->rgbTable);
        if (width == 0 || height == 0)
            isRGBEmpty = 1;
        bitMap->rgbTable = newRGBTable;
        bitMap->height = height;
        bitMap->width = width;
    }
    else
    {
        newYUVTable = (struct YUV **)malloc(height * sizeof(struct YUV *));
        for (int i = 0; i < height; i++)
        {
            newYUVTable[i] = (struct YUV *)malloc(width * sizeof(struct YUV));
        }
        if (isYUVEmpty == 1)
        {
            bitMap->yuvTable = newYUVTable;
            isYUVEmpty = 0;
            return;
        }

        for (uint32_t i = 0; i < height; i++)
        {
            memcpy(newYUVTable[i], bitMap->yuvTable[i], sizeof(struct YUV) * width);
        }

        for (int i = 0; i < bitMap->height; i++)
        {
            free(bitMap->yuvTable[i]);
        }
        free(bitMap->yuvTable);
        bitMap->yuvTable = newYUVTable;
        bitMap->height = height;
        bitMap->width = width;
        if (height == 0 || width == 0)
            isYUVEmpty = 1;
    }
}
void read_f(struct BMP *bmp, const char fileName[])
{
    if (strlen(fileName) == 0)
    {
        fprintf(stderr, "please input a imageName for read");
        exit(1);
    }
    FILE *file = fopen(fileName, "rb");
    if (!file)
    {
        fprintf(stderr, "this file doesn't exist");
        exit(1);
    }
    bmp->bitMap.colorSpace = RGB;
    bmp->bmpHead.readBmpHead(&bmp->bmpHead, file, 0);
    bmp->dibHead.readDibHead(&bmp->dibHead, file, 0);
    bmp->bitMap.height = bmp->dibHead.height;
    bmp->bitMap.width = bmp->dibHead.width;
    uint32_t heightAbs = floor(abs(bmp->dibHead.height)), widthAbs = floor(abs(bmp->dibHead.width));
    uint32_t lineSize = ((uint32_t)(bmp->dibHead.bits_per_pixel * widthAbs)) / 8;
    lineSize += (4 - lineSize % 4) % 4;
    bmp->bitMap.changeSize(&bmp->bitMap, heightAbs, widthAbs);

    fseek(file, bmp->bmpHead.offset, SEEK_SET);

    for (int i = 0; i < heightAbs; i++)
    {
        fread(bmp->bitMap.rgbTable[i], lineSize, 1, file);
    }
    fclose(file);
}
void write_f(struct BMP *bmp, const char fileName[])
{
    if (bmp->bitMap.colorSpace == YUV)
    {
        bmp->yuvToRGB(bmp);
    }
    if (strlen(fileName) == 0)
    {
        fprintf(stderr, "please input a fileName for output");
        exit(1);
    }
    FILE *file = fopen(fileName, "wb");
    uint32_t heightAbs = floor((bmp->bitMap.height)), widthAbs = floor((bmp->bitMap.width));
    bmp->dibHead.bits_per_pixel = 24;
    bmp->bmpHead.size = 54 + bmp->dibHead.bits_per_pixel / 8 * heightAbs * (widthAbs % 4 + widthAbs);
    bmp->bmpHead.offset = 54;
    bmp->bmpHead.reserved2 = bmp->bmpHead.reserved1 = 0;
    bmp->bmpHead.writeBmpHead(&bmp->bmpHead, file);

    bmp->dibHead.imageSize = bmp->dibHead.bits_per_pixel / 8 * heightAbs * (widthAbs % 4 + widthAbs);
    bmp->dibHead.width = widthAbs;
    bmp->dibHead.height = heightAbs;
    bmp->dibHead.plane = 1;
    bmp->dibHead.compression = 0;

    bmp->dibHead.pixels_per_y = bmp->dibHead.pixels_per_x = 3780;
    bmp->dibHead.colors = bmp->dibHead.importantColors = 0;
    bmp->dibHead.writeDibHead(&bmp->dibHead, file);

    uint32_t lineSize = bmp->dibHead.bits_per_pixel / 8 * widthAbs;
    uint32_t needToAdd = (4 - lineSize % 4) % 4;
    uint8_t *arrayNeededToAdd = (uint8_t *)malloc(needToAdd);
    memset(arrayNeededToAdd, 0, needToAdd);
    for (int it = 0; it < heightAbs; it++)
    {
        fwrite(bmp->bitMap.rgbTable[it], lineSize, 1, file);
        fwrite(arrayNeededToAdd, sizeof(uint8_t), needToAdd, file);
    }
    free(arrayNeededToAdd);
    fclose(file);
}
double temp(double input)
{
    if (input > 255)
        return 255;
    if (input < 0)
        return 0;
    return input;
}
void rgbToYUV_f(struct BMP *bmp)
{
    if (bmp->bitMap.colorSpace == RGB)
    {
        bmp->bitMap.colorSpace = YUV;
        bmp->bitMap.changeSize(&bmp->bitMap, floor((bmp->bitMap.height)), floor((bmp->bitMap.width)));
        struct RGB *rgb;
        struct YUV *yuv;
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            for (int j = 0; j < bmp->bitMap.width; j++)
            {
                rgb = &bmp->bitMap.rgbTable[i][j];
                yuv = &bmp->bitMap.yuvTable[i][j];
                yuv->y = 0.299 * rgb->r + 0.587 * rgb->g + 0.114 * rgb->b;
                yuv->v = 0.500 * rgb->r - 0.419 * rgb->g - 0.081 * rgb->b + 128;
                yuv->u = -0.169 * rgb->r - 0.331 * rgb->g + 0.500 * rgb->b + 128;
            }
        }
    }
};
void yuvToRGB_f(struct BMP *bmp)
{
    if (bmp->bitMap.colorSpace == YUV)
    {
        bmp->bitMap.colorSpace = RGB;
        struct RGB *rgbTemp;
        struct YUV *yuvTemp;
        double temp;
        bmp->bitMap.changeSize(&bmp->bitMap, floor((bmp->bitMap.height)), floor((bmp->bitMap.width)));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            for (int j = 0; j < bmp->bitMap.width; j++)
            {
                rgbTemp = &bmp->bitMap.rgbTable[i][j];
                yuvTemp = &bmp->bitMap.yuvTable[i][j];
                temp = yuvTemp->y + 1.13983 * (yuvTemp->v - 128);
                if (temp > 255)
                    temp = 255;
                else if (temp < 0)
                    temp = 0;
                rgbTemp->r = temp;
                temp = yuvTemp->y - 0.39465 * (yuvTemp->u - 128) - 0.58060 * (yuvTemp->v - 128);
                if (temp > 255)
                    temp = 255;
                else if (temp < 0)
                    temp = 0;
                rgbTemp->g = temp;
                temp = yuvTemp->y + 2.03211 * (yuvTemp->u - 128);
                if (temp > 255)
                    temp = 255;
                else if (temp < 0)
                    temp = 0;
                rgbTemp->b = temp;
            }
        }
    }
}
//只能在rgb空间内调用
void toGrayScale_f(struct BMP *bmp)
{
    double tmp;
    if (bmp->bitMap.colorSpace == RGB)
    {
        bmp->rgbToYUV(bmp);
    }
    for (int i = 0; i < bmp->bitMap.height; i++)
    {
        for (int j = 0; j < bmp->bitMap.width; j++)
        {
            bmp->bitMap.rgbTable[i][j].r = bmp->bitMap.rgbTable[i][j].g = bmp->bitMap.rgbTable[i][j].b =
                bmp->bitMap.yuvTable[i][j].y;
        }
    }
    for (int i = 0; i < bmp->bitMap.height; i++)
    {
        free(bmp->bitMap.yuvTable[i]);
    }
    free(bmp->bitMap.yuvTable);
    bmp->bitMap.colorSpace = RGB;
    isYUVEmpty = 1;
}

void meanFilterHelper(struct BMP *bmp, struct OperationType type, Unit filter[3][3], int calType)
{
    if (type.gray)
    {
        bmp->toGrayScale(bmp);
        newRGBTable = (struct RGB **)malloc(bmp->bitMap.height * sizeof(struct RGB *));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            newRGBTable[i] = (struct RGB *)(malloc(bmp->bitMap.width * (sizeof(struct RGB))));
            memcpy(newRGBTable[i], bmp->bitMap.rgbTable[i], sizeof(struct RGB) * bmp->bitMap.width);
        }
        for (int i = 0; i < bmp->bitMap.height; i++) {
          for (int j = 0; j < bmp->bitMap.width; j++) {
            double total = 0;
            int valid = 0;
            for (int iMove = 0; iMove < 3; iMove++) {
              for (int jMove = 0; jMove < 3; jMove++) {
                int newW = filter[iMove][jMove].w + j;
                int newH = filter[iMove][jMove].h + i;
                if (newW < 0 || newW >= bmp->bitMap.width)
                  continue;
                if (newH < 0 || newH >= bmp->bitMap.height)
                  continue;
                valid += filter[iMove][jMove].weight;
                total +=
                    filter[iMove][jMove].weight * (bmp->bitMap.rgbTable)[newH][newW].r;
              }
            }
            if (calType == 1) {
              int temp = total / valid;
              if (temp < 0)
                temp = 0;
              if (temp >= 255)
                temp = 255;
              (newRGBTable)[i][j].r = temp;
            } else {
              if (total > 255)
                total = 255;
              else if (total < 0)
                total = 0;
              (newRGBTable)[i][j].r = total;
            }
          }
        }
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            for (int j = 0; j < bmp->bitMap.width; j++)
            {
                newRGBTable[i][j].g = newRGBTable[i][j].b = newRGBTable[i][j].r;
                memcpy(newRGBTable[i], bmp->bitMap.rgbTable[i], sizeof(struct RGB) * bmp->bitMap.width);
            }
        }
        for (int i = 0; i < bmp->bitMap.height; i++)
            free(bmp->bitMap.rgbTable[i]);
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        newRGBTable = NULL;
        return;
    }
    if (type.red)
    {
        newRGBTable = (struct RGB **)malloc(bmp->bitMap.height * sizeof(struct RGB *));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            newRGBTable[i] = (struct RGB *)(malloc(bmp->bitMap.width * (sizeof(struct RGB))));
            memcpy(newRGBTable[i], bmp->bitMap.rgbTable[i], sizeof(struct RGB) * bmp->bitMap.width);
        }

                for (int i = 0; i < bmp->bitMap.height; i++) {
                  for (int j = 0; j < bmp->bitMap.width; j++) {
                    double total = 0;
                    int valid = 0;
                    for (int iMove = 0; iMove < 3; iMove++) {
                      for (int jMove = 0; jMove < 3; jMove++) {
                        int newW = filter[iMove][jMove].w + j;
                        int newH = filter[iMove][jMove].h + i;
                        if (newW < 0 || newW >= bmp->bitMap.width)
                          continue;
                        if (newH < 0 || newH >= bmp->bitMap.height)
                          continue;
                        valid += filter[iMove][jMove].weight;
                        total +=
                            filter[iMove][jMove].weight * (bmp->bitMap.rgbTable)[newH][newW].r;
                      }
                    }
                    if (calType == 1) {
                      int temp = total / valid;
                      if (temp < 0)
                        temp = 0;
                      if (temp >= 255)
                        temp = 255;
                      (newRGBTable)[i][j].r = temp;
                    } else {
                      if (total > 255)
                        total = 255;
                      else if (total < 0)
                        total = 0;
                      (newRGBTable)[i][j].r = total;
                    }
                  }
                }
        for (int i = 0; i < bmp->bitMap.height; i++)
            free(bmp->bitMap.rgbTable[i]);
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        newRGBTable = NULL;
    }
    if (type.green)
    {
        newRGBTable = (struct RGB **)malloc(bmp->bitMap.height * sizeof(struct RGB *));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            newRGBTable[i] = (struct RGB *)(malloc(bmp->bitMap.width * (sizeof(struct RGB))));
            memcpy(newRGBTable[i], bmp->bitMap.rgbTable[i], sizeof(struct RGB) * bmp->bitMap.width);
        }
        for (int i = 0; i < bmp->bitMap.height; i++) {
          for (int j = 0; j < bmp->bitMap.width; j++) {
            double total = 0;
            int valid = 0;
            for (int iMove = 0; iMove < 3; iMove++) {
              for (int jMove = 0; jMove < 3; jMove++) {
                int newW = filter[iMove][jMove].w + j;
                int newH = filter[iMove][jMove].h + i;
                if (newW < 0 || newW >= bmp->bitMap.width)
                  continue;
                if (newH < 0 || newH >= bmp->bitMap.height)
                  continue;
                valid += filter[iMove][jMove].weight;
                total +=
                    filter[iMove][jMove].weight * (bmp->bitMap.rgbTable)[newH][newW].g;
              }
            }
            if (calType == 1) {
              int temp = total / valid;
              if (temp < 0)
                temp = 0;
              if (temp >= 255)
                temp = 255;
              (newRGBTable)[i][j].g = temp;
            } else {
              if (total > 255)
                total = 255;
              else if (total < 0)
                total = 0;
              (newRGBTable)[i][j].g = total;
            }
          }
        }
        for (int i = 0; i < bmp->bitMap.height; i++)
            free(bmp->bitMap.rgbTable[i]);
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        newRGBTable = NULL;
    }
    if (type.blue)
    {
        newRGBTable = (struct RGB **)malloc(bmp->bitMap.height * sizeof(struct RGB *));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            newRGBTable[i] = (struct RGB *)(malloc(bmp->bitMap.width * (sizeof(struct RGB))));
            memcpy(newRGBTable[i], bmp->bitMap.rgbTable[i], sizeof(struct RGB) * bmp->bitMap.width);
        }
        for (int i = 0; i < bmp->bitMap.height; i++) {
          for (int j = 0; j < bmp->bitMap.width; j++) {
            double total = 0;
            int valid = 0;
            for (int iMove = 0; iMove < 3; iMove++) {
              for (int jMove = 0; jMove < 3; jMove++) {
                int newW = filter[iMove][jMove].w + j;
                int newH = filter[iMove][jMove].h + i;
                if (newW < 0 || newW >= bmp->bitMap.width)
                  continue;
                if (newH < 0 || newH >= bmp->bitMap.height)
                  continue;
                valid += filter[iMove][jMove].weight;
                total +=
                    filter[iMove][jMove].weight * (bmp->bitMap.rgbTable)[newH][newW].b;
              }
            }
            if (calType == 1) {
              int temp = total / valid;
              if (temp < 0)
                temp = 0;
              if (temp >= 255)
                temp = 255;
              (newRGBTable)[i][j].b = temp;
            } else {
              if (total > 255)
                total = 255;
              else if (total < 0)
                total = 0;
              (newRGBTable)[i][j].b = total;
            }
          }
        }
        for (int i = 0; i < bmp->bitMap.height; i++)
            free(bmp->bitMap.rgbTable[i]);
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        newRGBTable = NULL;
    }
}
void meanFilter_f(struct BMP *bmp, struct OperationType type)
{
    //进行灰度过滤
    Unit filter[3][3];
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            filter[i + 1][j + 1].h = i;
            filter[i + 1][j + 1].w = j;
            filter[i + 1][j + 1].weight = 1.0;
        }
    }
    meanFilterHelper(bmp, type, filter, 1);
}
void laplaceTrans_f(struct BMP *bmp, struct OperationType type)
{
    Unit filter[3][3];
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            filter[i + 1][j + 1].h = i;
            filter[i + 1][j + 1].w = j;
            filter[i + 1][j + 1].weight = -1;
        }
    }
    filter[1][1].weight = 8;
    meanFilterHelper(bmp, type, filter, 0);
}
void laplaceEnhance_f(struct BMP *bmp, struct OperationType type, double rate)
{
    Unit filter[3][3];
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            filter[i + 1][j + 1].h = i;
            filter[i + 1][j + 1].w = j;
            filter[i + 1][j + 1].weight = -rate;
        }
    }
    filter[1][1].weight = 1 + 8 * rate;
    meanFilterHelper(bmp, type, filter, 1);
}
//初始化函数
void initialize(struct BMP *bmpFile)
{
    isRGBEmpty = isYUVEmpty = 1;

    bmpFile->bmpHead.readBmpHead = readBMPHead_f;
    bmpFile->bmpHead.writeBmpHead = writeBmpHead_f;

    bmpFile->dibHead.readDibHead = readDibHead_f;
    bmpFile->dibHead.writeDibHead = writeDibHead_f;

    bmpFile->bitMap.changeSize = changeSize_f;

    bmpFile->read = read_f;
    bmpFile->write = write_f;
    bmpFile->yuvToRGB = yuvToRGB_f;
    bmpFile->rgbToYUV = rgbToYUV_f;
    bmpFile->toGrayScale = toGrayScale_f;
    bmpFile->meanFilter = meanFilter_f;
    bmpFile->laplaceTrans = laplaceTrans_f;
    bmpFile->laplaceEnhance = laplaceEnhance_f;
}
#endif // DIP_HW1_DIP_H