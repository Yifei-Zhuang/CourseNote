# **Lab 2.3** Buffer Overflow Vulnerability

## **Overview**

The learning objective of this lab is for students to gain the first-hand experience on buffer-overflow vulnerability by putting what they have learned about the vulnerability from class into actions. Buffer overflow is defined as the condition in which a program attempts to write data beyond the boundaries of pre-allocated fixed length buffers. This vulnerability can be utilized by a malicious user to alter the flow control of the program, even execute arbitrary pieces of code. This vulnerability arises due to the mixing of the storage for data (e.g. buffers) and the storage for controls (e.g. return addresses): an overflow in the data part can affect the control flow of the program, because an overflow can change the return address.

In this lab, you will be given a program with a buffer-overflow vulnerability; your task is to develop a scheme to exploit the vulnerability and finally to gain the root privilege. It uses Ubuntu VM created in Lab 2.1. Ubuntu 12.04 is recommended.

## Step 1  Initial setup. Disable Address Space Randomization.

为了关闭随机化，我们首先使用`sudo -i`进入root 模式。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/peC7tK.png)

使用`sysctl -w kernel.randomize_va_space=0`关闭随机化。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/hgKyyv.png)

## Step 2 create Vulnerable Program

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/1oUrTc.png)

## Step 3 Compile

使用`gcc -g -m32 -o stack -z execstack -fno-stack-protector stack.c`生成可执行文件。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Jr0fN1.png)

## Step 4 Complete the vulnerability code

创建`exploit.c`文件。

![image-20230427145611404](../../../../../../Library/Application Support/typora-user-images/image-20230427145611404.png)

按照实验手册的要求，我们最终的目标就是通过缓冲区溢出攻击修改stack.c中的 bof 函数的返回地址为 code 的首地址，以此完成攻击，我们首先使用 gdb 调试 stack 程序，查看bof函数的汇编代码。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/FpAk9b.png)

这里我们需要获得 buffer 的地址，在进入 bof 之后，我们可以使用`print &buffer`来获取 buffer 的地址，可以看到地址是0xffffce64

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/WYD4wt.png)

为了获得返回地址，我们使用info frame查看栈帧，其中 eip 寄存器存储了返回地址的地址，是0xffffce7c。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/qP6SPh.png)

可以看到两个地址之间的差值是0xffffce7c - 0xffffce64 = 0x18，所以我们如果需要覆盖返回地址，只需要在buffer + 0x18的位置加上 code 的地址就行，我们可以假定 code 存储在buffer + 0x100的位置，所以最终我们需要添加的代码就是。

```c
const char hackAddress[] = "\x64\xcf\xff\xff";
strcpy(buffer + 0x18,hackAddress);
strcpy(buffer + 0x100,code);
```

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/JL0nBX.png)