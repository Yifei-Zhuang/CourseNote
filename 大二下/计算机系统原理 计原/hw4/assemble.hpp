#ifndef __assemble
#define __assemble
#include "utils.hpp"
// 输出指令对应的二进制代码
inline void printMachineCode(uint32_t command);

//检查寄存器和立即数是否合法
inline bool check(initializer_list<int> registers = {}, int dat = 0,
                  int maxval = 0);

class Assembler
{
public:
    //将指令中的寄存器替换为$ + 数字的形式
    static void parseRegister(string &input);

    //进行汇编
    uint32_t __Assemble(string &input);
    //接受cli输入 汇编
    uint32_t Assemble(string input);
};
#endif