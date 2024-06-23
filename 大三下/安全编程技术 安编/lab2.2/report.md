# **Lab 2.2** Running a Hello World Program in C using GCC

##### 3200105872 软工 2020 庄毅非

## **Overview**

The lab helps familiarize you with writing a simple Hello World program using C, the GCC compiler [link](http://gcc.gnu.org/), and Pico(a text editor, [link](<http://en.wikipedia.org/wiki/Pico_(text_editor)>)). It uses Ubuntu VM created in Lab 2.1.Here is lab objective:

1. Learn to run a program in gcc.
2. Learn to debug a program in gdb.

## Open the Terminal in Ubuntu.

### 1. 安装必要套件

为了完成实验，我们首先需要安装 gcc 和 gdb，命令是`sudo apt install build-essential`

### 2. Create 'debug_me.c':

使用 vim，将题目中的 c 程序放到`debug_me.c`文件中

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/9NKvey.png)

### 3. Invoke gdb to debug 'debug_me.c':

使用`gcc -g debug_me.c -o debug_me`进行编译，使用 gdb 运行。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/vfjyLU.png)

## 4. Run the program inside gdb:

运行 run "hello, world" "goodbye, world"，查看输出。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/IOPhwx.png)

## 5. Set breakpoints. You can set breakpoints using two methods:

使用两种方式设置断点。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/7NYVuv.png)

## 6. Step a command at a time. After setting breakpoints, you can run the program step by step. There are also two methods:

使用两种 next 和 step 两种方式继续程序运行，区别主要在于后者如果是函数调用的话会进入到子函数里面，前者则不会。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rUqLLq.png)

## 7. Print variables

使用 print 观察变量的值.

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/s97tdI.png)

## 8. Examine the function call stack.

使用 where 观察函数调用链。

![image-20230427135942204](../../../../../../Library/Application Support/typora-user-images/image-20230427135942204.png)

可以看到 frame 0 实际上是没有 i 的，原因是没有定义，只有主函数 main 定义了 i。
