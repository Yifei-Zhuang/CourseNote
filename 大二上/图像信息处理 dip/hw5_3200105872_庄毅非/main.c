#include "dip.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        puts("usage: ./dip imageName.bmp");
        exit(0);
    }
    //读取文件
    struct BMP *bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    struct OperationType type = {0, 1, 1, 1};
    bmpFile->meanFilter(bmpFile, type);
    bmpFile->write(bmpFile, "RGBMeanFilter.bmp");
    free(bmpFile);

    struct BMP *bmpFile2 = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile2);
    bmpFile2->read(bmpFile2, argv[1]);
    struct OperationType type2 = {0, 1, 1, 1};
    bmpFile2->laplaceTrans(bmpFile2, type2);
    bmpFile2->write(bmpFile2, "LaplaceTrans.bmp");
    free(bmpFile2);

    struct BMP *bmpFile3 = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile3);
    bmpFile3->read(bmpFile3, argv[1]);
    struct OperationType type3 = {0, 1, 1, 1};
    double diff;
    printf("input the rate you want to do LaplaceEnhancement");
    scanf("%lf", &diff);
    bmpFile3->laplaceEnhance(bmpFile3, type3, diff);
    bmpFile3->write(bmpFile3, "LaplaceEnhanceFunc.bmp");
    free(bmpFile3);
    return 0;
}
