# **Lab 3.1** Using splint for C static analysis

## Overview

这个实验主要是教我们如何使用 c 静态分析工具splint。



## Step 1 下载Splint

这里按照给出的链接下载就行。

## Step 2 Extract and setup Splint.

这一步主要是在虚拟机中编译splint，生成可执行的splint程序，运行的命令如下。

```bash
tar -zxvf splint-3.1.2.linux.tgz
sudo mkdir /usr/local/splint
cd spint-3.1.2
sudo apt-get install flex
make -j4
sudo make install
```

需要注意的是，在执行`make -j4`的时候编译器输出了错误信息，如图所示。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/fb9KRT.png)

Google 之后发现这好像是 flex 的 bug，调试之后展示无法解决，所以在接下来的部分我迁移到了本机（maxOS 上完成），大部分命令都相同，只是需要使用`brew install flex`安装一下flex套件即可。

在 macOS 中编译完之后可以在bin文件夹下找到splint文件，如图所示。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/exYYlc.png)

## Step 3 编写有问题的代码

```c
#include<stdio.h>

int main(){
	// unused vars;
	int a;
	int b;
    // dereferencing null pointer
    int *pointer = NULL;
    a = *pointer;
	return 0;
}

```

## Step 4 使用 splint 嗅探

这里在命令行执行`./splint sample.c`就行，可以看到splint输出了我们故意留下的问题，分别是存在未使用的变量，以及解引用空指针。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/tOgYz9.png)

# **Lab 3.2** Using eclipse for java static analysis

## Overview

这个实验主要是教授我们使用 eclipse 进行 java 语言的静态分析。

## Step 1 Install plugins

由于我的电脑之前没有安装过eclipse，所以这里使用功能类似的 Intellij IDEA 完成实验。

我们打开 IDEA 的插件市场，这里我选择 PMD 进行安装。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/kDEvKW.png)

## Step 2 编辑问题代码

这里使用一个存在许多 bug 的 java 程序为例。

```java
package com.htl.secure_programming;

import java.util.Scanner;
import java.util.Scanner; // duplicate import

public class Bugs {
    public static void def(int a) {
        // unused method parameters
        return;
    }

    private void unusedMethod() {
        // unused private methods
        return;
    }

    // short method names
    private void a() {

    }

    // long method names
    // unused private method
    private void aa8123912i312g3u1k3h13khj312h3jk13h32aaaaaaaaaaaaaaaaaaaaa() {

    }

    public static void main(String[] args) {
        int a = 0;
        int b; // unused local vars
        Scanner in = new Scanner(System.in);
        try {

        } catch (Exception e) {
            // empty catch blocks
            def(a);
        }
        // always true
        if (1 == 1) {
            // empty block
        }
        // dead loop
        while (true) {

        }
    }
}

```

## Step 3 运行 PMD

这里右击文件，选择runpmd->predefined->all，就可以运行扫描。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/UIlOwU.png)

可以看到 PMD 插件扫描出了众多代码中存在的问题。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/pWB1og.png)