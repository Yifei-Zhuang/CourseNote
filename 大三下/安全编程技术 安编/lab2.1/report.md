# **Lab 2.1** Setting up Ubuntu Linux with VMWare Player

###### 3200105872 软工 2020  庄毅非

## **Overview**

Linux is a great environment for programming because the tools are readily available. And, there are some utilities you can only access using Linux. You have a few options for running Linux on a Windows PC:

- Use Putty (or other terminal emulation software) to log into a remote Linux server via SSH.
- Run Linux on your local Windows PC. Using :
  - Dual boot computer
    - This can be time-consuming to set up
    - This is good if you are doing lots of computational work or graphics
  - Use cygwin
    - People rarely do this
  - Use a Linux from a bootup disk
    - This is great for certain uses
  - You can set up Linux to run in virtually using VMware player - So EASY!
    - There are other utilities you can use such as [VirtualBox](https://www.virtualbox.org/).
    - In our lab, we will use VMWare Player

The lab uses Ubuntu Linux.The cool thing about using VMWare Player is that you can have different flavors of Linux running (at the same time) in different players. This gives you a chance to evaluate which one you like best. Here is lab objective:

1. Setting up Ubuntu Linux with VMWare Player
2. Learn to edit a file in **vi** Text Editor.

## Step 1 Download & Install VMWare Player

​	实验手册中要求安装`VMWare Player`，但是`VMWare Player`不支持我使用的 macOS 系统，所以这里采用 VMWare Fushion 完成实验，从官网上下载安装包，安装好之后如图所示。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/rVszKx.png)

## Step 2 Download Ubuntu

​	这里我选择 Ubuntu 22.04 LTS版本下载，下载好之后如图所示。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/OfYxP9.png)

## Step 3 Set up Ubuntu Linux with VMWare Player.

​	这里就按照 vmware 的提示安装就行，具体内容就不演示了。

## Step 4 Edit a file in **vi** Text Editor.

​	这里打开终端，执行`vi hello.txt`命令

​	![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/69ZjW0.png)

​	在编辑器中输入`Hello world!`。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/VBIsNl.png)

​	按 esc 进入命令模式，输入:wq退出 vi。

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/6mYYga.png)

使用 cat 查看文件内容

![](https://hutao-image-bed.oss-cn-hangzhou.aliyuncs.com/uPic/Glc3qH.png)