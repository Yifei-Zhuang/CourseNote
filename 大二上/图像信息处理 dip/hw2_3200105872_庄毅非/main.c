#include "dip.h"
#define erol 9 // length of eroser, jusr for test
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        puts("usage: ./execFileName imageName");
        exit(0);
    }
    //创建腐蚀和膨胀单元
    int **eroser = (int **)malloc(sizeof(int *) * erol);
    for (int i = 0; i < erol; i++)
    {
        eroser[i] = (int *)malloc(sizeof(int) * erol);
        eroser[i][0] = i % 3 - 1;
        eroser[i][1] = i % 3 - 1;
    }
    for (int i = 0; i < 9; i++)
    {
        eroser[i][0] = i % 3 - 1;
        eroser[i][1] = i % 3 - 1;
    }
    //读取文件
    struct BMP *bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->globalBinarization(bmpFile);
    bmpFile->write(bmpFile, "binary.bmp");
    free(bmpFile);
    bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->localBinarization(bmpFile, bmpFile->dibHead.width / 4, bmpFile->dibHead.width / 6);
    bmpFile->write(bmpFile, "binary_local.bmp");
    free(bmpFile);
    bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->globalBinarization(bmpFile);
    bmpFile->erosion(bmpFile, eroser, 9);
    bmpFile->write(bmpFile, "erosion.bmp");
    free(bmpFile);
    bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->globalBinarization(bmpFile);
    bmpFile->delation(bmpFile, eroser, 9);
    bmpFile->write(bmpFile, "dilation.bmp");
    free(bmpFile);
    bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->globalBinarization(bmpFile);
    bmpFile->opening(bmpFile, eroser, 9);
    bmpFile->write(bmpFile, "opening.bmp");
    free(bmpFile);
    bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->globalBinarization(bmpFile);
    bmpFile->closing(bmpFile, eroser, 9);
    bmpFile->write(bmpFile, "closing.bmp");
    free(bmpFile);
    return 0;
}
