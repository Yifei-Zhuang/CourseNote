#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
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

static vector<instruction> instInfo(51);
static map<int, string> registerMap = {
    {0, "$zero"}, {1, "$at"}, {2, "$v0"}, {3, "$v1"}, {4, "$a0"}, {5, "$a1"}, {6, "$a2"}, {7, "$a3"}, {8, "$t0"}, {9, "$t1"}, {10, "$t2"}, {11, "$t3"}, {12, "$t4"}, {13, "$t5"}, {14, "$t6"}, {15, "$t7"}, {16, "$s0"}, {17, "$s1"}, {18, "$s2"}, {19, "$s3"}, {20, "$s4"}, {21, "$s5"}, {22, "$s6"}, {23, "$s7"}, {24, "$t8"}, {25, "$t9"}, {26, "$k0"}, {27, "$k1"}, {28, "$gp"}, {29, "$sp"}, {30, "$fp"}, {31, "$ra"}};

void init()
{
  ifstream instinput("instructions");
  for (int i = 0; i < 51; i++)
    instinput >> instInfo[i];
  instinput.close();
}
void trim(string &str)
{
  if (str.empty())
    return;
  str.erase(0, str.find_first_not_of(' '));
  str.erase(str.find_last_not_of(' ') + 1);
}
inline void printMachineCode(uint32_t command)
{
  for (int i = 31; i >= 0; i--)
    cout << ((command >> i) & 0x01);
  puts("");
}
inline bool check(initializer_list<int> registers = {}, int dat = 0,
                  int maxval = 0)
{
  if (dat > maxval)
    return false;
  return all_of(registers.begin(), registers.end(),
                [](int index) -> bool
                { return index >= 0 && index <= 31; });
}
void parseRegister(string &input)
{
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
  //将input中的寄存器(也就是$xxx)转化为$%d的格式
  char *pre = &input[0], *beh;
  while (*pre)
  {
    while (*pre && *pre != '$')
      pre++;
    string reg;
    if (*pre == '$')
    {
      //进行寄存器位置的解析
      beh = pre;
      while (*beh && *beh != ',')
        reg.append({*(beh++)});
      if (!(reg[1] >= 'a' && reg[1] <= 'z') &&
          !(reg[1] >= 'A' && reg[1] <= 'Z'))
      {
        //解析到data 回到循环中
        pre = beh;
      }
      else
      {
        int index = -1;
        for (auto it : registerMap)
        {
          if (it.second == reg)
          {
            index = it.first;
            break;
          }
        }
        if (index == -1)
        {
          throw runtime_error("invalid register " + reg);
        }
        *pre = '\0';
        string backup = input.assign(&input[0]);
        backup.append({'$'});
        backup += to_string(index);
        while (*beh)
        {
          backup.append({*beh});
          beh++;
        }
        input = backup;
        pre = &input[0];
      }
    }
  }
  //  cout << input << endl;
}
uint32_t Assemble(string &input)
{
  int rs = 0, rt = 0, rd = 0, dat = 0, adr = 0, rc = 0;
  trim(input);
  transform(input.begin(), input.begin() + input.find_first_of(' '),
            input.begin(), ::toupper);
  string operation = input.substr(0, input.find(' '));
  auto typeInfo =
      find_if(instInfo.begin(), instInfo.end(),
              [&](instruction &it) -> bool
              { return it.name == operation; });
  if (typeInfo == instInfo.end())
  {
    throw runtime_error("invalid instruction");
  }
  input.erase(input.begin(), input.begin() + input.find_first_of(' ') + 1);
  if (input.size() && input.back() == ')')
    input.pop_back();
  //解析字符串，将字符串中的寄存器替换为$digit的格式
  parseRegister(input);
  switch (typeInfo->type)
  {
  case 'R':
  {
    sscanf(&input[0], "$%d,$%d,$%d", &rd, &rs, &rt);
    if (!check({rd, rs, rt}))
    {
      throw runtime_error("invalid register");
    }
    uint32_t result = 0;
    result |= typeInfo->op;
    result <<= 5, result |= rs;
    result <<= 5, result |= rt;
    result <<= 5, result |= rd;
    result <<= 5;
    result <<= 6, result |= typeInfo->fun;
    return result;
  }
  case 'I':
  {
    if (typeInfo->name == "LUI")
      sscanf(&input[0], "$%d,%d", &rt, &dat);
    else
    {
      sscanf(&input[0], "$%d,%d", &rs, &dat); //这里把ofs记为dat(位数一样)
      rt = 17;
    }
    if (!check({rs, rd, rt}, dat, 65535))
      throw runtime_error("invalid operation ");
    uint32_t result = 0;
    result |= typeInfo->op;
    result <<= 5, result |= rs;
    result <<= 5, result |= rt;
    result <<= 16, result |= (dat & 0x0ffff);
    return result;
  }
  case 'D':
  {
    sscanf(&input[0], "$%d,$%d,%d", &rt, &rs,
           &dat); //这里把ofs记为dat(位数一样)
    if (!check({rs, rt}, dat, 65535))
      throw runtime_error("invalid operation ");
    uint32_t result = typeInfo->op;
    result <<= 5, result |= rs;
    result <<= 5, result |= rt;
    result <<= 16, result |= dat;
    //      printMachineCode(result);
    return result;
  }
  case 'H':
  {
    sscanf(&input[0], "$%d,%d($%d)", &rt, &dat, &rs);
    if (!check({rs, rt}, dat, 65535))
      throw runtime_error("invalid operation ");
    uint32_t result = typeInfo->op;
    result <<= 5, result |= rs;
    result <<= 5, result |= rt;
    result <<= 16, result |= dat;
    //      printMachineCode(result);
    return result;
  }
  case 'J':
  {
    sscanf(&input[0], "%d", &adr);
    if (!check({}, dat, (1 << 26) - 1))
      throw runtime_error("invalid operation ");
    uint32_t result = typeInfo->op;
    result <<= 26, result |= adr;
    //      printMachineCode(result);
    return result;
  }
  case 'U':
  {
    if (typeInfo->name == "MFHI" || typeInfo->name == "MFLo")
      sscanf(&input[0], "$%d", &rd);
    else
      sscanf(&input[0], "$%d", &rs);
    if (!check({rs, rd}))
      throw runtime_error("invalid registers ");
    ;
    uint32_t result = typeInfo->op;
    result <<= 5, result |= rs;
    result <<= 10, result |= rd;
    result <<= 11, result |= typeInfo->fun;
    // printMachineCode(result);
    return result;
  }
  case 'P':
  {
    uint32_t result = typeInfo->op;
    if (operation == "JALR")
    {
      sscanf(&input[0], "$%d,$%d", &rs, &rd);
      result <<= 5, result |= rs;
      result <<= 10, result |= rd;
      result <<= 11, result |= typeInfo->fun;
    }
    else if (operation == "MFC0" || operation == "MTC0")
    {
      sscanf(&input[0], "$%d,$%d", &rt, &rc);
      result <<= 5;
      if (operation == "MFC0")
        result |= 0;
      else
        result |= 4;
      result <<= 5, result |= rt;
      result <<= 5, result |= rc;
      result <<= 11;
    }
    else
    {
      sscanf(&input[0], "$%d,$%d", &rs, &rt);
      result <<= 5, result |= rs;
      result <<= 5, result |= rt;
      result <<= 16, result |= typeInfo->fun;
    }
    if (!check({rd, rt, rs}))
    {
      throw runtime_error("invalid registers");
    }
    return result;
  }
  case 'S':
  {
    if (operation == "ERET")
    {
      return uint32_t(0b01000010000000000000000000011000);
    }
    else
    {
      return uint32_t(0b00000000000000000000000000001100);
    }
  }
  default:
  {
    throw runtime_error("unknown operation type");
  };
  }
}
int main()
{
  init();
  freopen("input.asm", "r", stdin);
  ofstream outFile("output", ios::out | ios::binary);
  string input;
  while (getline(cin, input))
  {
    if (input[0] == 'q')
    {
      break;
    }
    try
    {
      uint32_t result = Assemble(input);
      outFile.write((char *)&result, sizeof(result));
    }
    catch (exception e)
    {
      cerr << "无效输入" << endl;
      exit(1);
    };
  }
  return 0;
}
