#include "dip.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: ./imgHw3 imgName.bmp");
    exit(0);
  }
  //读取文件
  struct BMP *bmpFile = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile);
  bmpFile->read(bmpFile, argv[1]);
  struct OperationType type = {1, 0, 0, 0};
  bmpFile->logarithmicEnhancement(bmpFile, type, 0, 1 / 255.0, 2);
  bmpFile->write(bmpFile, "./grayLogTransformation.bmp");
  free(bmpFile);

  struct BMP *bmpFile2 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile2);
  bmpFile2->read(bmpFile2, argv[1]);
  type.gray = 0;
  type.red = type.blue = type.green = 1;
  bmpFile2->logarithmicEnhancement(bmpFile2, type, 0, 1 / 255.0, 2);
  bmpFile2->write(bmpFile2, "./rgbLogTransformation.bmp");
  free(bmpFile2);

  struct BMP *bmpFile3 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile3);
  bmpFile3->read(bmpFile3, argv[1]);
  type.gray = 0;
  type.red = 0;
  type.blue = 0;
  type.green = 1;
  bmpFile3->histogramEqualization(bmpFile3, type, 256);
  bmpFile3->write(bmpFile3, "./greenEquation.bmp");
  free(bmpFile3);

  struct BMP *bmpFile4 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile4);
  bmpFile4->read(bmpFile4, argv[1]);
  type.gray = 1;
  type.red = 0;
  type.blue = 0;
  type.green = 0;
  bmpFile4->histogramEqualization(bmpFile4, type, 256);
  bmpFile4->write(bmpFile4, "./grayEquation.bmp");
  free(bmpFile4);

  struct BMP *bmpFile5 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile5);
  bmpFile5->read(bmpFile5, argv[1]);
  type.gray = 0;
  type.red = 1;
  type.blue = 0;
  type.green = 0;
  bmpFile5->histogramEqualization(bmpFile5, type, 256);
  bmpFile5->write(bmpFile5, "./redEquation.bmp");
  free(bmpFile5);

  struct BMP *bmpFile6 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile6);
  bmpFile6->read(bmpFile6, argv[1]);
  type.gray = 0;
  type.red = 0;
  type.blue = 1;
  type.green = 0;
  bmpFile6->histogramEqualization(bmpFile6, type, 256);
  bmpFile6->write(bmpFile6, "./blueEquation.bmp");
  free(bmpFile6);

  struct BMP *bmpFile7 = (struct BMP *)malloc(sizeof(struct BMP));
  initialize(bmpFile7);
  bmpFile7->read(bmpFile7, argv[1]);
  type.gray = 0;
  type.red = 1;
  type.blue = 1;
  type.green = 1;
  bmpFile7->histogramEqualization(bmpFile7, type, 256);
  bmpFile7->write(bmpFile7, "./allRGBEquation.bmp");
  free(bmpFile7);
  return 0;
}
