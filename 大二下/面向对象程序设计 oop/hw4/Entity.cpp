#include "Entity.hpp"
// #define DEBUG
void Entity::setDate(string &date_string) { date = date_string; }
string &Entity::getDate() { return date; }

void Entity::setContent(vector<string> &Content) {
  diary_content.resize(Content.size());
  int size = Content.size();
  for (int i = 0; i < size; i++) {
    diary_content[i] = std::move(Content[i]);
  }
}
vector<string> &Entity::getContent() { return diary_content; }

inline std::vector<std::string>::size_type Entity::getSize() {
  return diary_content.size();
}
ostream &operator<<(ostream &out, Entity e) {
  out << e.date << endl;
  for_each(e.diary_content.begin(), e.diary_content.end(),
           [&](auto it) -> void { out << it << endl; });
  out << "." << endl;
  return out;
}
void Entity::readIn(istream &in) {
  string line, date;
  getline(in, date);
  setDate(date);
  getline(in, line);
  while (line != "." && !in.eof()) {
    diary_content.push_back(line);
    getline(in, line);
  }
}

// #ifdef DEBUG
// int main()
// {
//     auto pointer = LoadData();
//     if (pointer)
//     {
//         vector<string> newtemp;
//         newtemp.push_back("100");
//         newtemp.push_back("300");
//         (*pointer)[0].setContent(newtemp);
//         WriteData((*pointer));
//         delete pointer;
//     }
//     return 0;
// }
// #endif