#ifndef __DisAssembler
#define __DisAssembler
#include "utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class DisAssembler
{
public:
  /*
    op: operation code
    rs,rt,rd: register
    sa,fun,dat,adr: remain data in back of instruction
  */
  uint32_t op = 0, rs, rt, rd, sa, fun = 0, dat, adr;
  /*
    @param:  operation: the machine operation code consist of 1s and 0s
    @return: mips assemble command like add $a0,$a1,$a2
  */
  string __disAssemble(uint32_t operation);
  /*
    @param:  operation: the machine operation code consist of 1s and 0s
    @return: mips assemble command like add $a0,$a1,$a2
  */
  string disAssemble(const string &input);
  string disAssemble(uint32_t input);
};

#endif