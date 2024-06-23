#include "Entity.hpp"
#include "utils.cpp"
int main(int argc, char *argv[]) {
  vector<Entity> *entities = LoadData();

  if (argc == 1) {
    cout << "There is " << entities->size() << "diaries" << endl;
    sort((entities)->begin(), entities->end(),
         [](Entity a, Entity b) { return a.getDate() < b.getDate(); });
    for_each(entities->begin(), entities->end(),
             [&](auto it) -> void { cout << it; });
  } else if (argc == 3) {
    string lowdate = argv[1];
    string highdate = argv[2];
    vector<Entity> vec;
    for_each(entities->begin(), entities->end(), [&](auto it) -> void {
      if (it.getDate() >= lowdate && it.getDate() <= highdate) {
        vec.push_back(it);
      }
    });
    sort((vec).begin(), vec.end(),
         [](Entity a, Entity b) { return a.getDate() < b.getDate(); });
    cout << "there are " << vec.size() << " records\n";
    for_each(vec.begin(), vec.end(), [&](auto it) -> void { cout << (it); });
  } else {
    cerr << "usage: pdlist; \tor\t pdlist lowest date highest date" << endl;
  }
  delete entities;
  return 0;
}
