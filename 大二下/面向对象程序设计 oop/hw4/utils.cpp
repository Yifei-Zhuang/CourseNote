#include "utils.hpp"
void WriteData(vector<Entity> &entities) {
  ofstream out("diary", ios_base::out);
  int size = entities.size();
  out << size << endl;

  for (int i = 0; i < size; i++) {
    out << (entities[i]);
  }
  out.close();
}
// 当没有日记的时候，返回空的vector
vector<Entity> *LoadData() {
  string diary_count_str;
  int diary_count = 0;
  ifstream in("diary", ios::in);
  if (in.eof()) return new vector<Entity>(0);
  getline(in, diary_count_str);
  diary_count = std::stoi(diary_count_str);
  vector<Entity> *diaries = new vector<Entity>(diary_count);
  for (int i = 0; i < diary_count && !in.eof(); i++) {
    (*diaries)[i].readIn(in);
  }
  in.close();
  return diaries;
}
