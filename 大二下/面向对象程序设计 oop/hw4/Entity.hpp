#ifndef __diary__
#define __diary__
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Entity {
 private:
  string date;
  vector<string> diary_content;

 public:
  Entity() = default;
  void setDate(string &date_string);
  string &getDate();

  void setContent(vector<string> &Content);
  vector<string> &getContent();

  void readIn(istream &in);
  inline std::vector<std::string>::size_type getSize();
  friend ostream &operator<<(ostream &out, Entity e);
};
#endif