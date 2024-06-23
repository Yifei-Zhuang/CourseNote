#include "disAssembler.hpp"

/*
  @param:  operation: the machine operation code consist of 1s and 0s
  @return: mips assemble command like add $a0,$a1,$a2
*/
string DisAssembler::__disAssemble(uint32_t operation)
{
  op = operation >> 26;
  rs = (operation >> 21) & 0x0000001f;
  rt = (operation >> 16) & 0x0000001f;
  rd = (operation >> 11) & 0x0000001f;
  sa = (operation >> 7) & 0x0000001f;
  fun = (operation)&0x0000003f;
  dat = (operation)&0x0000ffff;
  adr = (operation)&0x03ffffff;
  if (op != 0 && op != 16)
    fun = 0;

  string result;
  auto type = find_if(
      instInfo.begin(), instInfo.end(),
      [&](instruction &i) -> bool
      { return i.op == op && i.fun == fun; });
  // if instruction not found, just throw a error
  if (type == instInfo.end())
    throw runtime_error("cannot parse this instrution");

  switch (type->type)
  {
  // type R: instruction r1,r2,r3
  case ('R'):
    result = concatStrings({type->name, " ", registerMap[rd], ",",
                            registerMap[rs], ",", registerMap[rt]});
    break;
  // type I: instruction r1,dat
  case ('I'):
    result = concatStrings(
        {type->name, " ",
         (type->name == "LUI" ? registerMap[rt] : registerMap[rs]), ",",
         to_string(dat)});
    break;
  // type D: instruction rt,ts,dat
  case ('D'):
    result = concatStrings({type->name, " ", registerMap[rt], ",",
                            registerMap[rs], ",", to_string(dat)});
    break;
  // type H: instruction rt,data(rs)
  case ('H'):
    result = concatStrings({type->name, " ", registerMap[rt], ",",
                            to_string(dat), "(", registerMap[rs], ")"});
    break;
  // type ​J: instruction adr
  case ('J'):
    result = concatStrings({type->name, " ", to_string(adr)});
    break;
  // type P: instruction r1,r2
  case ('P'):
    if (type->name == "JALR")
      result = concatStrings(
          {type->name, " ", registerMap[rs], ",", registerMap[rd]});
    else if ((type->name == "MFC0"))
    {
      if (rs == 0)
        result = concatStrings(
            {type->name, " ", registerMap[rt], ",", registerMap[rd]});
      else
        result = concatStrings(
            {"MTC0", " ", registerMap[rt], ",", registerMap[rd]});
    }
    else
      result = concatStrings(
          {type->name, " ", registerMap[rs], ",", registerMap[rt]});
    break;
  // type S:​ instruction
  case ('S'):
    result = std::move(type->name);
    break;
  // type ​U: instruction r1
  case ('U'):
    if (type->name == "MFLO" || type->name == "MFHI")
    {
      result = concatStrings({type->name, " ", registerMap[rd]});
    }
    else
    {
      result = concatStrings({type->name, " ", registerMap[rs]});
    }
    break;
  }
  return result;
}
string DisAssembler::disAssemble(const string &input)
{
  uint32_t operation = 0;
  string operation_input = input;
  trim(operation_input);
  transform(operation_input.begin(), operation_input.end(), operation_input.begin(), ::toupper);
  if (operation_input.length() != 32)
  {
    throw runtime_error("invalid machine code, please check its length: " +
                        operation_input);
  }
  trim(operation_input);
  try
  {
    operation = stringUint32(operation_input);
  }
  catch (exception e)
  {
    cout << e.what() << endl;
  }
  return this->__disAssemble(operation);
}
string DisAssembler::disAssemble(uint32_t input)
{
  string pre = "";
  for (int i = 31; i >= 0; i--)
    pre += (to_string((input >> i) & 0x01));
  return this->disAssemble(pre);
}