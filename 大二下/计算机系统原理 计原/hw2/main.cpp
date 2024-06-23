#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
uint32_t stringUint32(string &input) {
  uint32_t result = 0;
  const char *temp = input.c_str();
  for (int i = 0; i < input.size(); i++) {
    result |= (temp[i] - '0');
    if (i != input.size() - 1) result <<= 1;
  }
  return result;
}
string intToString(int code) {
  string result("");
  while (code) {
    result += ((code & 1) + '0');
    code >>= 1;
  }
  reverse(result.begin(), result.end());
  return result;
}
void trim(string &str) {
  if (str.empty()) return;
  str.erase(0, str.find_first_not_of(' '));
  str.erase(str.find_last_not_of(' ') + 1);
}
class instruction {
 public:
  string name;
  uint32_t op;
  uint32_t fun;
  char type;
  friend istream &operator>>(istream &is, instruction &i) {
    is >> i.name >> i.op >> i.fun >> i.type;
    return is;
  }
};

static vector<instruction> instInfo(51);
static map<int, string> registerMap = {
    {0, "$zero"}, {1, "$at"},  {2, "$v0"},  {3, "$v1"},  {4, "$a0"},
    {5, "$a1"},   {6, "$a2"},  {7, "$a3"},  {8, "$t0"},  {9, "$t1"},
    {10, "$t2"},  {11, "$t3"}, {12, "$t4"}, {13, "$t5"}, {14, "$t6"},
    {15, "$t7"},  {16, "$s0"}, {17, "$s1"}, {18, "$s2"}, {19, "$s3"},
    {20, "$s4"},  {21, "$s5"}, {22, "$s6"}, {23, "$s7"}, {24, "$t8"},
    {25, "$t9"},  {26, "$k0"}, {27, "$k1"}, {28, "$gp"}, {29, "$sp"},
    {30, "$fp"},  {31, "$ra"}};

class decompiler {
 public:
  uint32_t op = 0, rs, rt, rd, sa, fun = 0, dat, adr;
  void printInfo() {
    puts("");
    printf("op: %u, rs: %u, rt: %u, rd: %u, sa: %u, fun: %u, dat:%u, adr: %u",
           op, rs, rt, rd, sa, fun, dat, adr);
    puts("");
  }
  string concatStrings(initializer_list<string> il) {
    string result;
    for (auto &it : il) result += it;
    return result;
  }
  string decompile(uint32_t operation) {
    // printf("%x\n",operation);
    op = operation >> 26;
    rs = (operation >> 21) & 0x0000001f;
    rt = (operation >> 16) & 0x0000001f;
    rd = (operation >> 11) & 0x0000001f;
    sa = (operation >> 7) & 0x0000001f;
    fun = (operation)&0x0000003f;
    dat = (operation)&0x0000ffff;
    adr = (operation)&0x03ffffff;
    if (op != 0 && op != 16) fun = 0;
    string result;
    // printInfo();
    auto type = find_if(
        instInfo.begin(), instInfo.end(),
        [&](instruction &i) -> bool { return i.op == op && i.fun == fun; });

    if (type == instInfo.end()) {
      throw runtime_error("cannot parse this instrution");
      ;
    }
    switch (type->type) {
      case ('R'):
        result = concatStrings({type->name, " ", registerMap[rd], ",",
                                registerMap[rs], ",", registerMap[rt]});
        break;
      case ('I'):
        result = concatStrings(
            {type->name, " ",
             (type->name == "LUi" ? registerMap[rt] : registerMap[rs]), ",",
             to_string(dat)});
        break;
      case ('D'):
        result = concatStrings({type->name, " ", registerMap[rt], ",",
                                registerMap[rs], ",", to_string(dat)});
        break;
      case ('H'):
        result = concatStrings({type->name, " ", registerMap[rt], ",",
                                to_string(dat), "(", registerMap[rs], ")"});
        break;
      case ('J'):
        result = concatStrings({type->name, " ", to_string(adr)});
        break;
      case ('P'):
        if (type->name == "JALr")
          result = concatStrings(
              {type->name, " ", registerMap[rs], ",", registerMap[rd]});
        else if ((type->name == "MFC0")) {
          if (rs == 0)
            result = concatStrings(
                {type->name, " ", registerMap[rt], ",", registerMap[rd]});
          else
            result = concatStrings(
                {"MTC0", " ", registerMap[rt], ",", registerMap[rd]});
        } else
          result = concatStrings(
              {type->name, " ", registerMap[rs], ",", registerMap[rt]});
        break;
      case ('S'):
        result = std::move(type->name);
        break;
      case ('U'):
        if (type->name == "MFLo" || type->name == "MFHi") {
          result = concatStrings({type->name, " ", registerMap[rd]});
        } else {
          result = concatStrings({type->name, " ", registerMap[rs]});
        }
        break;
    }
    return result;
  }
};

void init() {
  ifstream instinput("instructions");
  for (int i = 0; i < 51; i++) instinput >> instInfo[i];
  instinput.close();
}
int main() {
  init();
  //   freopen("MachineCode","r",stdin);
  while (1) {
    string operation_input;
    getline(cin, operation_input);
    if (operation_input.length() == 0 || operation_input[0] == 'q') {
      break;
    }
    if (operation_input.length() != 32)
      throw runtime_error("invalid machine code, please check its length");
    trim(operation_input);
    uint32_t operation = stringUint32(operation_input);
    decompiler d;
    string result = d.decompile(operation);
    cout << result << endl;
  }
  return 0;
}