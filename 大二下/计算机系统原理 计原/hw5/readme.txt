计算机系统原理 作业5
本程序实现了简单的点阵汉字输出，包括文件显示、放大、斜体、倒立、彩色、空心等，只能够在macos/Linux下运行（Windows编码方式和*nix不同，暂时不支持）。
程序的输入为a.txt,请在输入文本到a.txt文件之后进入本文件夹运行bash init.sh,之后运行 g++ a.cpp -o hw; ./hw即可运行程序。
运行程序后，本目录下会出现多个新文件，包括
    1. output.txt 原始点阵输出
    2. biggerOutput.txt 放大点阵输出
    3. handstandOutput.txt: 文字倒立输出
    4. italicOutput: 斜体输出
    5. kongxinOutput: 空心输出
彩色输出已经被实现，但是由于写入文件的时候颜色属性会造成编码问题，所以实现上我直接输出在终端了。
本程序只能够在macos/Linux下运行