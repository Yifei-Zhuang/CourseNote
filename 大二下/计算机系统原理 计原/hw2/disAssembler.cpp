#include "disAssembler.hpp"

// convert string to uint32_t
uint32_t stringUint32(string &input) {
  uint32_t result = 0;
  const char *temp = input.c_str();
  for (int i = 0; i < input.size(); i++) {
    result |= (temp[i] - '0');
    if (i != input.size() - 1) result <<= 1;
  }
  return result;
}
// convert int to string
string intToString(int code) {
  string result("");
  while (code) {
    result += ((code & 1) + '0');
    code >>= 1;
  }
  reverse(result.begin(), result.end());
  return result;
}
// remove space around string
void trim(string &str) {
  if (str.empty()) return;
  str.erase(0, str.find_first_not_of(' '));
  str.erase(str.find_last_not_of(' ') + 1);
}

// concat a string in a list
string DisAssembler::concatStrings(initializer_list<string> il) {
  string result;
  for (auto &it : il) result += it;
  return result;
}
/*
  @param:  operation: the machine operation code consist of 1s and 0s
  @return: mips assemble command like add $a0,$a1,$a2
*/
string DisAssembler::disAssemble(uint32_t operation) {
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
  auto type = find_if(
      instInfo.begin(), instInfo.end(),
      [&](instruction &i) -> bool { return i.op == op && i.fun == fun; });
  // if instruction not found, just throw a error
  if (type == instInfo.end()) 
    throw runtime_error("cannot parse this instrution");
  
  switch (type->type) {
    // type R: instruction r1,r2,r3
    case ('R'):
      result = concatStrings({type->name, " ", registerMap[rd], ",",
                              registerMap[rs], ",", registerMap[rt]});
      break;
    // type I: instruction r1,dat
    case ('I'):
      result = concatStrings(
          {type->name, " ",
           (type->name == "LUi" ? registerMap[rt] : registerMap[rs]), ",",
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
    // type S:​ instruction
    case ('S'):
      result = std::move(type->name);
      break;
    // type ​U: instruction r1
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

// read in metadata for all instructions like 'operation code' 'fun' etc.
void init() {
  ifstream instinput("instructions");
  for (int i = 0; i < 51; i++) instinput >> instInfo[i];
  instinput.close();
}

int main() {
  init();
  DisAssembler d;
  uint32_t operation = 0;
  while (1) {
    string operation_input;
    getline(cin, operation_input);
    if (operation_input.length() == 0 || operation_input[0] == 'q') {
      break;
    }
    if (operation_input.length() != 32) {
      cerr << ("invalid machine code, please check its length: " +
               operation_input);
      continue;
    }
    trim(operation_input);
    try {
      operation = stringUint32(operation_input);
    } catch (exception e) {
      cout << e.what() << endl;
      continue;
    }
    cout << d.disAssemble(operation) << endl;
  }
  return 0;
}