#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
class Course {
 public:
  Course() = default;
  Course(string name) : courseName(name){};
  string &getName() { return this->courseName; }
  friend bool operator<(const Course &a, const Course &b) {
    return a.courseName < b.courseName;
  }

 private:
  string courseName;
};
class Student {
 public:
  Student() = default;
  Student(string aName, int courseTaken)
      : name(aName), courseNum(courseTaken){};
  double calAverage() const {
    return 1.0 *
           accumulate(takes.begin(), takes.end(), 0,
                      [](int a, auto it) -> double { return a + it.second; }) /
           takes.size();
  }
  int getScore(Course &course) {
    auto it = takes.find(course);
    if (it == takes.end()) return -1;
    return it->second;
  }
  string &getName() { return name; }
  friend istream &operator>>(istream &in, Student &stu) {
    in >> stu.name >> stu.courseNum;
    string courseName;
    int courseScore;
    for (int i = 0; i < stu.courseNum; i++) {
      in >> courseName >> courseScore;
      if (stu.takes.find(Course{courseName}) == stu.takes.end())
        stu.takes[Course{courseName}] = courseScore;
    }
    return in;
  }

 private:
  int courseNum;
  string name;
  map<Course, int> takes;
};
vector<Course> courses;
vector<Student> students;
int getMax(Course &course, vector<Student> &stuVec = students) {
  int maxScore = -1;
  int curScore = -1;
  for (auto it : stuVec) {
    if ((curScore = it.getScore(course)) != -1 && curScore > maxScore) {
      maxScore = curScore;
    }
  }
  return maxScore;
}
int getMin(Course &course, vector<Student> &stuVec = students) {
  int minScore = std::numeric_limits<int>::max();
  int curScore = -1;
  for (auto it : stuVec) {
    if ((curScore = it.getScore(course)) != -1 && curScore < minScore) {
      minScore = curScore;
    }
  }
  return minScore;
}
double getAverage(Course &course, vector<Student> &stuVec = students) {
  double result = 0;
  int curScore = -1;
  int count = 0;
  for (auto it : stuVec) {
    if ((curScore = it.getScore(course)) != -1) {
      count++;
      result += 1.0 * curScore;
    }
  }
  if (count)
    return result / count;
  else
    return 0.0;
}
void output() {
  cout << left;
  cout << setw(10) << "no" << setw(10) << "name";
  for (auto it : courses) cout << setw(10) << it.getName();
  cout << setw(10) << "average" << endl;
  int score;
  for (int i = 0; i < students.size(); i++) {
    cout << setw(10) << i << setw(10) << students[i].getName();
    for (int j = 0; j < courses.size(); j++) {
      if ((score = students[i].getScore(courses[j])) != -1) {
        cout << setw(10) << score;
      } else {
        cout << setw(10) << " ";
      }
    }
    cout << setw(10) << students[i].calAverage();
    puts("");
  }
  cout << setw(10) << " " << setw(10) << "average";
  for_each(courses.begin(), courses.end(),
           [&](auto &it) -> void { cout << setw(10) << getAverage(it); });
  puts("");
  cout << setw(10) << " " << setw(10) << "max";
  for_each(courses.begin(), courses.end(),
           [&](auto &it) -> void { cout << setw(10) << getMax(it); });
  puts("");
  cout << setw(10) << " " << setw(10) << "min";
  for_each(courses.begin(), courses.end(),
           [&](auto &it) -> void { cout << setw(10) << getMin(it); });
  puts("");
}
int main() {
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  int courseNum = 0, stuNum = 0;
  string courseName;
  cin >> courseNum >> stuNum;
  students.resize(stuNum);
  for (int i = 0; i < courseNum; i++) {
    cin >> courseName;
    courses.push_back(Course{courseName});
  }
  for (int i = 0; i < stuNum; i++) {
    cin >> students[i];
  }
  output();
  return 0;
}