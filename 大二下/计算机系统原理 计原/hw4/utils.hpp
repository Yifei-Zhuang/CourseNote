#ifndef utils
#define utils
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;
// class of mips instruction
class instruction
{
public:
    string name;
    uint32_t op;
    uint32_t fun;
    char type;
    friend istream &operator>>(istream &is, instruction &i)
    {
        is >> i.name >> i.op >> i.fun >> i.type;
        return is;
    }
};
// mapping from register number to register name
map<int, string> registerMap = {
    {0, "$zero"}, {1, "$at"}, {2, "$v0"}, {3, "$v1"}, {4, "$a0"}, {5, "$a1"}, {6, "$a2"}, {7, "$a3"}, {8, "$t0"}, {9, "$t1"}, {10, "$t2"}, {11, "$t3"}, {12, "$t4"}, {13, "$t5"}, {14, "$t6"}, {15, "$t7"}, {16, "$s0"}, {17, "$s1"}, {18, "$s2"}, {19, "$s3"}, {20, "$s4"}, {21, "$s5"}, {22, "$s6"}, {23, "$s7"}, {24, "$t8"}, {25, "$t9"}, {26, "$k0"}, {27, "$k1"}, {28, "$gp"}, {29, "$sp"}, {30, "$fp"}, {31, "$ra"}};
// mips instruction container
vector<instruction> instInfo(51);
// 寄存器数据
int registers[32];

#define MEMSPACE 32
// 内存数据
uint32_t memory[uint64_t(1) << MEMSPACE];

// read in metadata for all instructions like 'operation code' 'fun' etc.
void init()
{
    cout << "正在初始化内存空间，请稍作等待\n";
    ifstream instinput("./instructions");
    for (int i = 0; i < 51; i++)
        instinput >> instInfo[i];
    instinput.close();
    // TODO change default value of registers
    // TODO change default value of memory
}
// convert string to uint32_t
uint32_t stringUint32(string &input)
{
    uint32_t result = 0;
    const char *temp = input.c_str();
    for (int i = 0; i < input.size(); i++)
    {
        result |= (temp[i] - '0');
        if (i != input.size() - 1)
            result <<= 1;
    }
    return result;
}
// convert int to string
string intToString(int code)
{
    string result("");
    while (code)
    {
        result += ((code & 1) + '0');
        code >>= 1;
    }
    reverse(result.begin(), result.end());
    return result;
}
// remove space around string
void trim(string &str)
{
    if (str.empty())
        return;
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
}

// concat a string in a list
string concatStrings(initializer_list<string> il)
{
    string result;
    for (auto &it : il)
        result += it;
    return result;
}

string intToHex(int a)
{
    string digits = "0123456789ABCDEF", result = "";
    for (int i = 28; i >= 0; i -= 4)
    {
        result += (digits[(a >> i) & 0x000F]);
    }
    return result;
}
uint32_t string_to_bit(const string &str)
{

    uint32_t result = strtoll(str.c_str(), NULL, 16);
    return result;
}

void showAllRegisters()
{
    int count;
    for (count = 1; count <= 32; count++)
    {
        cout << left << setw(15) << registerMap[count - 1] + ":" + to_string(registers[count - 1]);
        if (count && count % 8 == 0)
            puts("");
    }
}
void showMemory(int startPos = 0, int limits = 100)
{
    if (startPos < 0)
    {
        cerr << "start Pos cannot be negative\n"
             << endl;
        return;
    }
    if (startPos + limits >= ((uint64_t(1) << 32) - 1))
    {
        cerr << "memory overflow!\n"
             << endl;
        return;
    }
    int count = 1;
    for (int i = startPos; i < startPos + limits; i++)
    {
        cout << left << setw(25) << intToHex(i) + ":" + to_string(memory[i]);
        if (count++ % 5 == 0)
            puts("");
    }
    puts("");
}
#endif