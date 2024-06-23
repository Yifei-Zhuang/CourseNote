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
    void (*translation)(struct BMP *, int, int);
    void (*rotation)(struct BMP *, double);
    void (*scale)(struct BMP *, double, double);
    void (*mirror)(struct BMP *, int);
    void (*shear)(struct BMP *, int, double);
};

#endif // DIP_HW1_DIP_H

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
#ifdef DEBUG
    printf("BMP file size: %d, reserved: %d %d,\n"
           "offBit:%d,\n"
           "width:%d,height:%d\n"
           "planes:%d,bitsPerPixel:%d\n"
           "compresissio:%d\nimageSize:%d\n"
           "pixelsForX:%d,pixelsForY:%d\n"
           "Colors:%d,importantColors:%d\n",
           bmp->bmpHead.size, bmp->bmpHead.reserved1, bmp->bmpHead.reserved2, bmp->bmpHead.offset, bmp->dibHead.width,
           bmp->dibHead.height, bmp->dibHead.plane, bmp->dibHead.bits_per_pixel, bmp->dibHead.compression,
           bmp->dibHead.imageSize, bmp->dibHead.pixels_per_x, bmp->dibHead.pixels_per_y, bmp->dibHead.colors,
           bmp->dibHead.importantColors);
#endif
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

void translation_f(struct BMP *bmp, int x, int y)
{
    uint32_t height = bmp->bitMap.height + (x < 0 ? -x : x);
    uint32_t width = bmp->bitMap.width + (y < 0 ? -y : y);
    if (bmp->bitMap.colorSpace == RGB)
    {
        struct RGB *rgb, *newRGB;
        bmp->bitMap.changeSize(&bmp->bitMap, height, width);
        newRGBTable = (struct RGB **)malloc(height * sizeof(struct RGB *));
        for (int i = 0; i < height; i++)
        {
            newRGBTable[i] = (struct RGB *)malloc(width * sizeof(struct RGB));
            memset(newRGBTable[i], 0, sizeof(struct RGB) * width);
        }

        for (int i = 0; i < bmp->dibHead.height; i++)
        {
            for (int j = 0; j < bmp->dibHead.width; j++)
            {
                // 遍历原像素数组的每一个点，并将其搬运到新像素数组的位置
                struct RGB *temp = &newRGBTable[i + (x < 0 ? 0 : x)][j + (y < 0 ? 0 : y)];
                struct RGB *pre = &bmp->bitMap.rgbTable[i][j];
                temp->r = pre->r;
                temp->g = pre->g;
                temp->b = pre->b;
            }
        }
        for (int i = 0; i < height; i++)
            free(bmp->bitMap.rgbTable[i]);
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        newRGBTable = NULL;
    }
    else
    {
        struct YUV *rgb, *newYUV;
        bmp->bitMap.changeSize(&bmp->bitMap, height, width);
        newYUVTable = (struct YUV **)malloc(height * sizeof(struct YUV *));
        for (int i = 0; i < height; i++)
        {
            newYUVTable[i] = (struct YUV *)malloc(width * sizeof(struct YUV));
            memset(newYUVTable[i], 0, sizeof(struct YUV) * width);
        }

        for (int i = 0; i < bmp->dibHead.height; i++)
        {
            for (int j = 0; j < bmp->dibHead.width; j++)
            {
                struct YUV *temp = &newYUVTable[i + (x < 0 ? 0 : x)][j + (y < 0 ? 0 : y)];
                struct YUV *pre = &bmp->bitMap.yuvTable[i][j];
                temp->y = pre->y;
                temp->u = pre->u;
                temp->v = pre->v;
            }
        }
        for (int i = 0; i < height; i++)
            free(bmp->bitMap.yuvTable[i]);
        free(bmp->bitMap.yuvTable);
        bmp->bitMap.yuvTable = newYUVTable;
        newYUVTable = NULL;
    }
    bmp->dibHead.width = width;
    bmp->dibHead.height = height;
}
struct RGB *interpolation(struct BMP *bmp, double x, double y)
{
    struct RGB *res = (struct RGB *)malloc(sizeof(struct RGB));
    int x1 = floor(x), x2 = ceil(x), y1 = floor(y), y2 = ceil(y);
    if (x2 >= bmp->bitMap.height)
        x2 = bmp->bitMap.height - 1;
    if (x1 >= bmp->bitMap.height)
        x1 = bmp->bitMap.height - 1;
    if (y1 >= bmp->bitMap.width)
        y1 = bmp->bitMap.width - 1;
    if (y2 >= bmp->bitMap.width)
        y2 = bmp->bitMap.width - 1;
    if (x1 == x2 && y1 == y2)
    {
        return &bmp->bitMap.rgbTable[x1][y1];
    }
    else if (x1 == x2)
    {
        double ratioY = (y - y1) / (y2 - y1);
        res->r = ratioY * bmp->bitMap.rgbTable[x1][y1].r + (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].r;
        res->g = ratioY * bmp->bitMap.rgbTable[x1][y1].g + (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].g;
        res->b = ratioY * bmp->bitMap.rgbTable[x1][y1].b + (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].b;
    }
    else if (y1 == y2)
    {
        double ratioX = (x - x1) / (x2 - x1);
        res->r = ratioX * bmp->bitMap.rgbTable[x1][y1].r + (1 - ratioX) * bmp->bitMap.rgbTable[x2][y1].r;
        res->g = ratioX * bmp->bitMap.rgbTable[x1][y1].g + (1 - ratioX) * bmp->bitMap.rgbTable[x2][y1].g;
        res->b = ratioX * bmp->bitMap.rgbTable[x1][y1].b + (1 - ratioX) * bmp->bitMap.rgbTable[x2][y1].b;
    }
    else
    {
        double ratioX = (x - x1) / (x2 - x1), ratioY = (y - y1) / (y2 - y1);
        res->r = ratioX * ratioY * bmp->bitMap.rgbTable[x1][y1].r +
                 ratioX * (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].r +
                 (1 - ratioX) * ratioY * bmp->bitMap.rgbTable[x2][y1].r +
                 (1 - ratioX) * (1 - ratioY) * bmp->bitMap.rgbTable[x2][y2].r;
        res->g = ratioX * ratioY * bmp->bitMap.rgbTable[x1][y1].g +
                 ratioX * (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].g +
                 (1 - ratioX) * ratioY * bmp->bitMap.rgbTable[x2][y1].g +
                 (1 - ratioX) * (1 - ratioY) * bmp->bitMap.rgbTable[x2][y2].g;
        res->b = ratioX * ratioY * bmp->bitMap.rgbTable[x1][y1].b +
                 ratioX * (1 - ratioY) * bmp->bitMap.rgbTable[x1][y2].b +
                 (1 - ratioX) * ratioY * bmp->bitMap.rgbTable[x2][y1].b +
                 (1 - ratioX) * (1 - ratioY) * bmp->bitMap.rgbTable[x2][y2].b;
    }
    return res;
}
double myMin(double a, double b)
{
    return a < b ? a : b;
}
double myMax(double a, double b)
{
    return a > b ? a : b;
}
void rotation_f(struct BMP *bmp, double theta)
{
    // TODO 插值法
    int width = bmp->dibHead.width;
    int height = bmp->dibHead.height;
    int x1 = 0, y1 = 0, x2 = 0, y2 = height, x3 = width, y3 = 0, x4 = width, y4 = height;
    int x1m = x1 * cos(theta) - y1 * sin(theta), y1m = x1 * sin(theta) + y1 * cos(theta),
        x2m = x2 * cos(theta) - y2 * sin(theta), y2m = x2 * sin(theta) + y2 * cos(theta),
        x3m = x3 * cos(theta) - y3 * sin(theta), y3m = x3 * sin(theta) + y3 * cos(theta),
        x4m = x4 * cos(theta) - y4 * sin(theta), y4m = x4 * sin(theta) + y4 * cos(theta);
    double minX = 0x3f3f3f3f, minY = 0x3f3f3f3f, maxX = -0x3f3f3f3f, maxY = -0x3f3f3f3f;
    minX = (myMin(minX, myMin(x1m, myMin(x2m, myMin(x3m, x4m)))));
    minY = (myMin(minY, myMin(y1m, myMin(y2m, myMin(y3m, y4m)))));
    maxX = (myMax(maxX, myMax(x1m, myMax(x2m, myMax(x3m, x4m)))));
    maxY = (myMax(maxY, myMax(y1m, myMax(y2m, myMax(y3m, y4m)))));
    int newWidth = maxX - minX + 1;
    int newHeight = maxY - minY + 1;
    // TODO implement case YUV colorspace
    if (bmp->bitMap.colorSpace == RGB)
    {
        newRGBTable = (struct RGB **)malloc(sizeof(struct RGB *) * newHeight);
        for (int i = 0; i < newHeight; i++)
        {
            newRGBTable[i] = (struct RGB *)malloc(sizeof(struct RGB) * newWidth);
            memset(newRGBTable[i], 0, sizeof(struct RGB) * newWidth);
        }
        for (int i = 0; i < newHeight; i++)
            for (int j = 0; j < newWidth; j++)
            {
                double newY = ((i + minY) * cos(theta) - (j + minX) * sin(theta));
                double newX = ((i + minY) * sin(theta) + (j + minX) * cos(theta));
                if (newX < 0 || newX >= width || newY < 0 || newY >= height)
                    newX = newY = 0;
                if (newX == 0 || newY == 0)
                {
                    struct RGB temp = {0, 0, 0};
                    newRGBTable[i][j] = temp;
                }
                else
                    newRGBTable[i][j] = *interpolation(bmp, newY, newX);
            }
        for (int i = 0; i < height; i++)
        {
            free(bmp->bitMap.rgbTable[i]);
        }
        free(bmp->bitMap.rgbTable);
        bmp->bitMap.rgbTable = newRGBTable;
        bmp->bitMap.width = bmp->dibHead.width = newWidth;
        bmp->bitMap.height = bmp->dibHead.height = newHeight;
    }
    else
    {
        newYUVTable = (struct YUV **)malloc(sizeof(struct YUV *) * newHeight);
        for (int i = 0; i < newHeight; i++)
        {
            newYUVTable[i] = (struct YUV *)malloc(sizeof(struct YUV) * newWidth);
            memset(newYUVTable[i], 0, sizeof(struct YUV) * newWidth);
        }
        for (int i = 0; i < newHeight; i++)
            for (int j = 0; j < newWidth; j++)
            {
                int newY = ceil((i + minY) * cos(theta) - (j + minX) * sin(theta));
                int newX = ceil((i + minY) * sin(theta) + (j + minX) * cos(theta));
                if (newX < 0 || newX >= width || newY < 0 || newY >= height)
                    newX = newY = 0;
                if (newX == 0 || newY == 0)
                {
                    struct YUV temp = {0, 0, 0};
                    newYUVTable[i][j] = temp;
                }
                else
                    newYUVTable[i][j] = bmp->bitMap.yuvTable[newY][newX];
            }
        for (int i = 0; i < width; i++)
        {
            free(bmp->bitMap.yuvTable[i]);
        }
        free(bmp->bitMap.yuvTable);
        bmp->bitMap.yuvTable = newYUVTable;
        bmp->bitMap.width = bmp->dibHead.width = newWidth;
        bmp->bitMap.height = bmp->dibHead.height = newHeight;
    }
}
void scale_f(struct BMP *bmp, double heightPercent, double widthPercent)
{
    // TODO 插值法
    int isYUV = 0;
    if (bmp->bitMap.colorSpace == YUV)
    {
        isYUV = 1;
        bmp->yuvToRGB(bmp);
    }
    if (heightPercent == 0 || widthPercent == 0)
        return;
    uint32_t width = bmp->bitMap.width, height = bmp->bitMap.height;
    uint32_t newWidth = ceil(width * widthPercent), newHeight = ceil(height * heightPercent);
    newRGBTable = (struct RGB **)malloc(sizeof(struct RGB *) * newHeight);
    for (int i = 0; i < newHeight; i++)
        newRGBTable[i] = (struct RGB *)malloc(sizeof(struct RGB) * newWidth);
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            struct RGB *temp = &newRGBTable[i][j];
            struct RGB *temp2 =
                &bmp->bitMap.rgbTable[(uint32_t)floor(i / heightPercent)][(uint32_t)floor(j / widthPercent)];
            temp->r = temp2->r;
            temp->b = temp2->b;
            temp->g = temp2->g;
        }
    }
    for (int i = 0; i < height; i++)
        free(bmp->bitMap.rgbTable[i]);
    free(bmp->bitMap.rgbTable);
    bmp->bitMap.rgbTable = newRGBTable;
    bmp->bitMap.width = bmp->dibHead.width = newWidth;
    bmp->bitMap.height = bmp->dibHead.height = newHeight;
    if (isYUV)
    {
        bmp->rgbToYUV(bmp);
    }
}
/*
 * type:
 *  0表示无操作
 *  1表示水平反转
 *  2表示垂直反转
 *  3表示都反转
 * */
void reverseHiorzional(struct BMP *bmp)
{
    uint32_t width = bmp->bitMap.width;
    uint32_t height = bmp->bitMap.height;
    if (bmp->bitMap.colorSpace == RGB)
    {
        struct RGB temp;
        for (int i = 0; i < height; i++)
            for (int j = 0; j <= width / 2; j++)
            {
                temp.r = bmp->bitMap.rgbTable[i][j].r;
                temp.g = bmp->bitMap.rgbTable[i][j].g;
                temp.b = bmp->bitMap.rgbTable[i][j].b;

                bmp->bitMap.rgbTable[i][j].r = bmp->bitMap.rgbTable[i][width - j].r;
                bmp->bitMap.rgbTable[i][j].g = bmp->bitMap.rgbTable[i][width - j].g;
                bmp->bitMap.rgbTable[i][j].b = bmp->bitMap.rgbTable[i][width - j].b;

                bmp->bitMap.rgbTable[i][width - j].r = temp.r;
                bmp->bitMap.rgbTable[i][width - j].g = temp.g;
                bmp->bitMap.rgbTable[i][width - j].b = temp.b;
            }
    }
    else
    {
        struct YUV temp;
        for (int i = 0; i < height; i++)
            for (int j = 0; j <= width / 2; j++)
            {
                temp.y = bmp->bitMap.yuvTable[i][j].y;
                temp.u = bmp->bitMap.yuvTable[i][j].u;
                temp.v = bmp->bitMap.yuvTable[i][j].v;

                bmp->bitMap.yuvTable[i][j].y = bmp->bitMap.yuvTable[i][width - j].y;
                bmp->bitMap.yuvTable[i][j].u = bmp->bitMap.yuvTable[i][width - j].u;
                bmp->bitMap.yuvTable[i][j].v = bmp->bitMap.yuvTable[i][width - j].v;

                bmp->bitMap.yuvTable[i][width - j].y = temp.y;
                bmp->bitMap.yuvTable[i][width - j].u = temp.u;
                bmp->bitMap.yuvTable[i][width - j].v = temp.v;
            }
    }
}
void reverseVertical(struct BMP *bmp)
{
    int height = bmp->dibHead.height;
    if (bmp->bitMap.colorSpace == RGB)
    {
        struct RGB *move = NULL;
        for (int i = 0; i < height / 2; i++)
        {
            move = bmp->bitMap.rgbTable[i];
            bmp->bitMap.rgbTable[i] = bmp->bitMap.rgbTable[height - i - 1];
            bmp->bitMap.rgbTable[height - i] = move;
        }
    }
    else
    {
        struct YUV *move;
        for (int i = 0; i < height / 2; i++)
        {
            move = bmp->bitMap.yuvTable[i];
            bmp->bitMap.yuvTable[i] = bmp->bitMap.yuvTable[height - i];
            bmp->bitMap.yuvTable[height - i] = move;
        }
    }
}
void mirror_f(struct BMP *bmp, int type)
{
    if (!type)
        return;
    if (type == 1)
    {
        reverseVertical(bmp);
    }
    else if (type == 2)
    {
        reverseHiorzional(bmp);
    }
    else
    {
        reverseHiorzional(bmp);
        reverseVertical(bmp);
    }
}
void shear_f(struct BMP *bmp, int type, double diff)
{
    // TODO 插值法
    if (!type)
        return;
    diff = fabs(diff);
    if (type == 1)
    {
        // shear on x axis
        uint32_t width = bmp->dibHead.width + ceil(bmp->dibHead.height * diff);
        uint32_t height = bmp->dibHead.height;
        if (bmp->bitMap.colorSpace == RGB)
        {
            newRGBTable = (struct RGB **)malloc(height * sizeof(struct RGB *));
            for (int i = 0; i < height; i++)
            {
                newRGBTable[i] = (struct RGB *)malloc(width * sizeof(struct RGB));
                memset(newRGBTable[i], 0, sizeof(struct RGB) * width);
            }

            for (int i = 0; i < bmp->dibHead.height; i++)
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    newRGBTable[i][(uint32_t)(j + ceil(i * diff))] = bmp->bitMap.rgbTable[i][j];
                }
            for (int i = 0; i < bmp->dibHead.height; i++)
                free(bmp->bitMap.rgbTable[i]);
            free(bmp->bitMap.rgbTable);
            bmp->bitMap.rgbTable = newRGBTable;
            bmp->bitMap.width = bmp->dibHead.width = width;
            bmp->bitMap.height = bmp->dibHead.height = height;
            newRGBTable = NULL;
        }
        else
        {
            newYUVTable = (struct YUV **)malloc(height * sizeof(struct YUV *));
            for (int i = 0; i < height; i++)
            {
                newYUVTable[i] = (struct YUV *)malloc(width * sizeof(struct YUV));
                memset(newYUVTable[i], 0, sizeof(struct YUV) * width);
            }

            for (int i = 0; i < bmp->dibHead.height; i++)
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    newYUVTable[i][(uint32_t)(j + ceil(i * diff))] = bmp->bitMap.yuvTable[i][j];
                }
            for (int i = 0; i < bmp->dibHead.height; i++)
                free(bmp->bitMap.yuvTable[i]);
            free(bmp->bitMap.yuvTable);
            bmp->bitMap.yuvTable = newYUVTable;
            newYUVTable = NULL;
        }
    }
    else if (type == 2)
    {
        // shear on x axis
        uint32_t width = bmp->dibHead.width;
        uint32_t height = bmp->dibHead.height + ceil(bmp->dibHead.width * diff);

        if (bmp->bitMap.colorSpace == RGB)
        {
            newRGBTable = (struct RGB **)malloc(height * sizeof(struct RGB *));
            for (int i = 0; i < height; i++)
            {
                newRGBTable[i] = (struct RGB *)malloc(width * sizeof(struct RGB));
                memset(newRGBTable[i], 0, sizeof(struct RGB) * width);
            }

            for (int i = 0; i < bmp->dibHead.height; i++)
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    newRGBTable[i + (uint32_t)(j * diff)][j] = bmp->bitMap.rgbTable[i][j];
                }
            for (int i = 0; i < bmp->dibHead.height; i++)
                free(bmp->bitMap.rgbTable[i]);
            free(bmp->bitMap.rgbTable);
            bmp->bitMap.rgbTable = newRGBTable;
            bmp->bitMap.width = bmp->dibHead.width = width;
            bmp->bitMap.height = bmp->dibHead.height = height;
            newRGBTable = NULL;
        }
        else
        {
            newYUVTable = (struct YUV **)malloc(height * sizeof(struct YUV *));
            for (int i = 0; i < height; i++)
            {
                newYUVTable[i] = (struct YUV *)malloc(width * sizeof(struct YUV));
                memset(newYUVTable[i], 0, sizeof(struct YUV) * width);
            }

            for (int i = 0; i < bmp->dibHead.height; i++)
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    newYUVTable[i + (uint32_t)(j * diff)][j] = bmp->bitMap.yuvTable[i][j];
                }
            for (int i = 0; i < bmp->dibHead.height; i++)
                free(bmp->bitMap.yuvTable[i]);
            free(bmp->bitMap.yuvTable);
            bmp->bitMap.yuvTable = newYUVTable;
            newYUVTable = NULL;
        }
    }
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
    bmpFile->translation = translation_f;
    bmpFile->rotation = rotation_f;
    bmpFile->mirror = mirror_f;
    bmpFile->shear = shear_f;
    bmpFile->scale = scale_f;
}
