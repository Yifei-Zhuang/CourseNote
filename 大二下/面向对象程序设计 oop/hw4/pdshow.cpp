#include "Entity.hpp"
#include "utils.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "please input date you want to show diary" << endl;
    exit(1);
  }
  string date = argv[1];
  vector<Entity> *entities = LoadData();
  int hasFound = false;
  int index;
  for (index = 0; index < (*entities).size(); index++) {
    if ((*entities)[index].getDate() == date) {
      hasFound = true;
      break;
    }
  }
  if (!hasFound) {
    cout << "there is no this diary on date: " << date << endl;
  } else {
    cout << (*entities)[index];
  }
  delete entities;
  return 0;
}