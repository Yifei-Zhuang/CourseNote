#ifndef __DisAssembler
#define __DisAssembler
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// convert string to uint32_t
uint32_t stringUint32(string &input);

// convert int to string
string intToString(int code);

// remove space around string
void trim(string &str);

// class of mips instruction
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

class DisAssembler {
 public:
  // mapping from register number to register name
  inline static map<int, string> registerMap = {
      {0, "$zero"}, {1, "$at"},  {2, "$v0"},  {3, "$v1"},  {4, "$a0"},
      {5, "$a1"},   {6, "$a2"},  {7, "$a3"},  {8, "$t0"},  {9, "$t1"},
      {10, "$t2"},  {11, "$t3"}, {12, "$t4"}, {13, "$t5"}, {14, "$t6"},
      {15, "$t7"},  {16, "$s0"}, {17, "$s1"}, {18, "$s2"}, {19, "$s3"},
      {20, "$s4"},  {21, "$s5"}, {22, "$s6"}, {23, "$s7"}, {24, "$t8"},
      {25, "$t9"},  {26, "$k0"}, {27, "$k1"}, {28, "$gp"}, {29, "$sp"},
      {30, "$fp"},  {31, "$ra"}};
  /*
    op: operation code
    rs,rt,rd: register
    sa,fun,dat,adr: remain data in back of instruction
  */
  uint32_t op = 0, rs, rt, rd, sa, fun = 0, dat, adr;
  // concat a string in a list
  string concatStrings(initializer_list<string> il);
  /*
    @param:  operation: the machine operation code consist of 1s and 0s
    @return: mips assemble command like add $a0,$a1,$a2
  */
  string disAssemble(uint32_t operation);
};
// mips instruction container
static vector<instruction> instInfo(51);
// read in metadata for all instructions like 'operation code' 'fun' etc.
void init();

#endif