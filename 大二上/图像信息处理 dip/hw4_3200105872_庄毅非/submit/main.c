#include "dip.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        puts("usage: ./exec imageName.bmp");
        return 0;
    }
    //读取文件
    struct BMP *bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
    initialize(bmpFile);
    int diff_X = 0, diff_Y = 0;
    printf("translation:\n\t请输入您要在x轴和y轴方向上对图像做出的偏移量（比如： 100 100）\n\t");
    fflush(stdin);
    scanf("%d %d", &diff_X, &diff_Y);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->translation(bmpFile, diff_X, diff_Y);
    bmpFile->write(bmpFile, "./Translation.bmp");
    int type = 0;
    printf("mirror:\n\t请输入您想要执行的翻转类型，1表示垂直方向上进行翻转，2表示水平方向上进行翻转，3表示对角线翻转\n\t");
    fflush(stdin);
    scanf("%d", &type);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->mirror(bmpFile, type);
    bmpFile->write(bmpFile, "./Mirror.bmp");

    isRGBEmpty = 1;
    double ratio = 0;
    printf("shear:\n\t请输入您要执行shear的轴，1表示x轴，2表示y轴\n\t");
    fflush(stdin);
    scanf("%d", &type);
    printf("\t请输入您期望图片shear的程度\n\t");
    fflush(stdin);
    scanf("%lf", &ratio);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->shear(bmpFile, type, ratio);
    bmpFile->write(bmpFile, "./Sheer.bmp");

    double degree = 0;
    printf("rotate:\n\t请输入您想要将图片旋转的角度（角度制）\n\t");
    fflush(stdin);
    scanf("%lf", &degree);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->rotation(bmpFile, degree / 180 * acos(-1));
    bmpFile->write(bmpFile, "./Rotate.bmp");

    double xRatio = 1, yRatio = 1;
    printf("scale:\n\t请输入您在x方向上和y方向上对于图像进行的伸展或压缩的程度\n\t");
    fflush(stdin);
    scanf("%lf %lf", &xRatio, &yRatio);
    bmpFile->read(bmpFile, argv[1]);
    bmpFile->scale(bmpFile, xRatio, yRatio);
    bmpFile->write(bmpFile, "./Scale.bmp");
    free(bmpFile);
    return 0;
}
