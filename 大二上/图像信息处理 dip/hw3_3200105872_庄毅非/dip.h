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
struct OperationType
{
    int gray;
    int red;
    int green;
    int blue;
};
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
    void (*logarithmicEnhancement)(struct BMP *, struct OperationType, double,
                                   double, double);
    void (*histogramEqualization)(struct BMP *, struct OperationType, int);
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
    printf(
        "BMP file size: %d, reserved: %d %d,\n"
        "offBit:%d,\n"
        "width:%d,height:%d\n"
        "planes:%d,bitsPerPixel:%d\n"
        "compresissio:%d\nimageSize:%d\n"
        "pixelsForX:%d,pixelsForY:%d\n"
        "Colors:%d,importantColors:%d\n",
        bmp->bmpHead.size, bmp->bmpHead.reserved1, bmp->bmpHead.reserved2,
        bmp->bmpHead.offset, bmp->dibHead.width, bmp->dibHead.height,
        bmp->dibHead.plane, bmp->dibHead.bits_per_pixel, bmp->dibHead.compression,
        bmp->dibHead.imageSize, bmp->dibHead.pixels_per_x,
        bmp->dibHead.pixels_per_y, bmp->dibHead.colors,
        bmp->dibHead.importantColors);
#endif
    bmp->bitMap.height = bmp->dibHead.height;
    bmp->bitMap.width = bmp->dibHead.width;
    uint32_t heightAbs = floor(abs(bmp->dibHead.height)),
             widthAbs = floor(abs(bmp->dibHead.width));
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
    uint32_t heightAbs = floor((bmp->bitMap.height)),
             widthAbs = floor((bmp->bitMap.width));
    bmp->dibHead.bits_per_pixel = 24;
    bmp->bmpHead.size = 54 + bmp->dibHead.bits_per_pixel / 8 * heightAbs *
                                 (widthAbs % 4 + widthAbs);
    bmp->bmpHead.offset = 54;
    bmp->bmpHead.reserved2 = bmp->bmpHead.reserved1 = 0;
    bmp->bmpHead.writeBmpHead(&bmp->bmpHead, file);

    bmp->dibHead.imageSize =
        bmp->dibHead.bits_per_pixel / 8 * heightAbs * (widthAbs % 4 + widthAbs);
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
        bmp->bitMap.changeSize(&bmp->bitMap, floor((bmp->bitMap.height)),
                               floor((bmp->bitMap.width)));
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
        bmp->bitMap.changeSize(&bmp->bitMap, floor((bmp->bitMap.height)),
                               floor((bmp->bitMap.width)));
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
                temp = yuvTemp->y - 0.39465 * (yuvTemp->u - 128) -
                       0.58060 * (yuvTemp->v - 128);
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
            bmp->bitMap.rgbTable[i][j].r = bmp->bitMap.rgbTable[i][j].g =
                bmp->bitMap.rgbTable[i][j].b = bmp->bitMap.yuvTable[i][j].y;
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

double myLogFunction(double x, double a, double b, double c)
{
    double temp = a + log(x + 1) / (b * log(c));
    if (temp < 0)
        temp = 0;
    else if (temp > 255)
        temp = 255;
    return temp;
}

void logarithmicEnhancement_f(struct BMP *bmp, struct OperationType type,
                              double a, double b, double c)
{
    uint32_t width = bmp->dibHead.width;
    uint32_t height = bmp->bitMap.height;

    if (type.gray)
    {
        bmp->toGrayScale(bmp);
        double rMax = -0x3f3f3f3f;
        // get Y's max value
        for (int i = 0; i < bmp->dibHead.height; i++)
        {
            for (int j = 0; j < bmp->dibHead.width; j++)
            {
                rMax = (rMax > bmp->bitMap.rgbTable[i][j].r
                            ? rMax
                            : bmp->bitMap.rgbTable[i][j].r);
            }
        }
        // grayscale operation
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                bmp->bitMap.rgbTable[i][j].r = bmp->bitMap.rgbTable[i][j].g =
                    bmp->bitMap.rgbTable[i][j].b =
                        myLogFunction(bmp->bitMap.rgbTable[i][j].r / rMax, a, b, c);
            }
        }
    }
    else
    {
        if (type.blue)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].b = myLogFunction(
                        bmp->bitMap.rgbTable[i][j].b / 255.0, a, b, 2);
                }
            }
        }
        if (type.red)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].r = myLogFunction(
                        bmp->bitMap.rgbTable[i][j].r / 255.0, a, b, 2);
                }
            }
        }
        if (type.green)
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].g = myLogFunction(
                        bmp->bitMap.rgbTable[i][j].g / 255.0, a, b, 2);
                }
            }
        }
    }
}
void histogramEqualization_f(struct BMP *bmp, struct OperationType type,
                             int blocks)
{
    if (type.gray)
    {
        bmp->toGrayScale(bmp);
        double yMin = 0x3f3f3f3f, yMax = -0x3f3f3f3f;
        for (int i = 0; i < bmp->dibHead.height; i++)
        {
            for (int j = 0; j < bmp->dibHead.width; j++)
            {
                int temp = bmp->bitMap.rgbTable[i][j].r;
                yMin = yMin < temp ? yMin : temp;
                yMax = yMax > temp ? yMax : temp;
            }
        }
        double histogram[blocks + 1];
        double step = (yMax - yMin) / blocks;
        memset(histogram, 0, (blocks + 1) * sizeof(double));
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            for (int j = 0; j < bmp->bitMap.width; j++)
            {
                histogram[(int)round((bmp->bitMap.rgbTable[i][j].r - yMin) / step)]++;
            }
        }
        for (int i = 1; i <= blocks; i++)
        {
            histogram[i] += histogram[i - 1];
        }
        for (int i = 0; i < bmp->bitMap.height; i++)
        {
            for (int j = 0; j < bmp->bitMap.width; j++)
            {
                bmp->bitMap.rgbTable[i][j].r = bmp->bitMap.rgbTable[i][j].g =
                    bmp->bitMap.rgbTable[i][j].b =
                        histogram[(
                            int)(round((bmp->bitMap.rgbTable[i][j].r - yMin) / step))] /
                            (1.0 * (bmp->dibHead.height * bmp->bitMap.width)) *
                            (yMax - yMin) +
                        yMin;
            }
        }
    }
    else
    {
        if (type.green)
        {
            double gMin = 0x3f3f3f3f, gMax = -0x3f3f3f3f;
            for (int i = 0; i < bmp->dibHead.height; i++)
            {
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    int temp = bmp->bitMap.rgbTable[i][j].g;
                    gMin = gMin < temp ? gMin : temp;
                    gMax = gMax > temp ? gMax : temp;
                }
            }
            double histogram[blocks + 1];
            double step = (gMax - gMin) / blocks;
            memset(histogram, 0, (blocks + 1) * sizeof(double));
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    histogram[(int)round((bmp->bitMap.rgbTable[i][j].g - gMin) / step)]++;
                }
            }
            for (int i = 1; i <= blocks; i++)
            {
                histogram[i] += histogram[i - 1];
            }
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].g =
                        histogram[(
                            int)(round((bmp->bitMap.rgbTable[i][j].g - gMin) / step))] /
                            (1.0 * (bmp->dibHead.height * bmp->bitMap.width)) *
                            (gMax - gMin) +
                        gMin;
                }
            }
        }
        if (type.red)
        {
            double rMin = 0x3f3f3f3f, rMax = -0x3f3f3f3f;
            for (int i = 0; i < bmp->dibHead.height; i++)
            {
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    int temp = bmp->bitMap.rgbTable[i][j].r;
                    rMin = rMin < temp ? rMin : temp;
                    rMax = rMax > temp ? rMax : temp;
                }
            }
            double histogram[blocks + 1];
            double step = (rMax - rMin) / blocks;
            memset(histogram, 0, (blocks + 1) * sizeof(double));
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    histogram[(int)round((bmp->bitMap.rgbTable[i][j].r - rMin) / step)]++;
                }
            }
            for (int i = 1; i <= blocks; i++)
            {
                histogram[i] += histogram[i - 1];
            }
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].r =
                        histogram[(
                            int)(round((bmp->bitMap.rgbTable[i][j].r - rMin) / step))] /
                            (1.0 * (bmp->dibHead.height * bmp->bitMap.width)) *
                            (rMax - rMin) +
                        rMin;
                }
            }
        }
        if (type.blue)
        {
            double bMin = 0x3f3f3f3f, bMax = -0x3f3f3f3f;
            for (int i = 0; i < bmp->dibHead.height; i++)
            {
                for (int j = 0; j < bmp->dibHead.width; j++)
                {
                    int temp = bmp->bitMap.rgbTable[i][j].b;
                    bMin = bMin < temp ? bMin : temp;
                    bMax = bMax > temp ? bMax : temp;
                }
            }
            double histogram[blocks + 1];
            double step = (bMax - bMin) / blocks;
            memset(histogram, 0, (blocks + 1) * sizeof(double));
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    histogram[(int)round((bmp->bitMap.rgbTable[i][j].b - bMin) / step)]++;
                }
            }
            for (int i = 1; i <= blocks; i++)
            {
                histogram[i] += histogram[i - 1];
            }
            for (int i = 0; i < bmp->bitMap.height; i++)
            {
                for (int j = 0; j < bmp->bitMap.width; j++)
                {
                    bmp->bitMap.rgbTable[i][j].b =
                        histogram[(
                            int)(round((bmp->bitMap.rgbTable[i][j].b - bMin) / step))] /
                            (1.0 * (bmp->dibHead.height * bmp->bitMap.width)) *
                            (bMax - bMin) +
                        bMin;
                }
            }
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
    bmpFile->toGrayScale = toGrayScale_f;
    bmpFile->logarithmicEnhancement = logarithmicEnhancement_f;
    bmpFile->histogramEqualization = histogramEqualization_f;
}
