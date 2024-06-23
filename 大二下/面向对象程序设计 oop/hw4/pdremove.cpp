#include "Entity.hpp"
#include "utils.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "please input date you want to delete diary" << endl;
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
    entities->erase(entities->begin() + index, entities->begin() + index + 1);
    WriteData(*entities);
    cout << "delete diary on date: " << date << " successfully!" << endl;
  }
  delete entities;
  return 0;
}