#include "Entity.hpp"
#include "utils.cpp"
int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "please input date you want to create a diary on\n" << endl;
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
  vector<string> newContent;
  string input;
  getline(cin, input);
  while (!input.empty() && input != ".") {
    newContent.push_back(input);
    getline(cin, input);
  }
  if (hasFound) {
    ((*entities)[index].setContent(newContent));
    cout << "update diary on " << date << " successfully\n";
  } else {
    Entity temp;
    temp.setDate(date);
    temp.setContent(newContent);
    (*entities).push_back(temp);
    cout << "add diary on " << date << " successfully\n";
  }
  WriteData((*entities));
  delete entities;
  return 0;
}