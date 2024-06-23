使用方法：cmake .; make
程序从input.asc读取汇编代码，以二进制形式输出到output中
如果出现错误输入（比如"MFHI $k#dsa"），会输出"无效输入"
