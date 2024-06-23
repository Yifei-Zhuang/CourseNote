#include "dip.h"
void initialize(struct BMP *bmpFile)
{
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
    bmpFile->changeLuminance = changeLuminance_f;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: ./exec imageName.bmp");
        return 0;
    }
    struct BMP *bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->changeLuminance(bmpFile, 100);
    bmpFile->write(bmpFile, "luminance_100Test.bmp");

    bmpFile->read(bmpFile, argv[1]);
    bmpFile->toGrayScale(bmpFile);
    bmpFile->write(bmpFile, "grayScaleTest.bmp");
    free(bmpFile);

    return 0;
}
