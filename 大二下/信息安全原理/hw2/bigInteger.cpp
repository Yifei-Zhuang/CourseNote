#include "bigInteger.h"

void trans(string &a, vector<int> &input) {
  for (auto it = a.crbegin(); it != a.crend(); it++) {
    input.push_back(*it - '0');
  }
}
template <typename T>
inline void printVector(vector<T> &a) {
  for_each(a.crbegin(), a.crend(), [](T it) -> void { cout << it; });
  puts("");
}
bool compare(vector<int> &a, vector<int> &b) {
  if (a.size() < b.size())
    return false;
  else if (a.size() > b.size())
    return true;
  else {
    auto it1 = a.crbegin(), it2 = b.crbegin();
    while (it1 != a.crend()) {
      if (*it1 > *it2)
        return true;
      else if (*it1 < *it2) {
        return false;
      }
      it1++;
      it2++;
    }
    return true;
  }
}
// 一个写的比较naive的add函数

vector<int> adding(vector<int> &vec1, vector<int> &vec2) {
  // 这里输入的向量是正向的
  vector<int> result;
  auto it1 = vec1.cbegin(), it2 = vec2.cbegin();
  while (it1 != vec1.cend() && it2 != vec2.cend()) {
    result.push_back(*it1 + *it2);
    it1++;
    it2++;
  }
  while (it1 != vec1.cend()) {
    result.push_back(*it1);
    it1++;
  }
  while (it2 != vec2.cend()) {
    result.push_back(*it2);
    it2++;
  }
  for (int i = 0; i < result.size() - 1; i++) {
    if (result[i] >= 10) {
      result[i + 1] += result[i] / 10;
      result[i] %= 10;
    }
  }
  if (result.back() >= 10) {
    result.insert(result.end(), result.back() / 10);
    result[result.size() - 2] %= 10;
  }
  return result;
}
vector<int> mul(vector<int> &vec1, vector<int> &vec2) {
  vector<int> result(vec1.size() + vec2.size() + 1, 0);
  for (int i = 0; i < vec1.size(); i++)
    for (int j = 0; j < vec2.size(); j++) {
      result[i + j] += vec1[i] * vec2[j];
    }
  int finalPos = 0, move = 0;
  for (; move < vec1.size() + vec2.size(); move++) {
    if (result[move]) finalPos = move;
    if (result[move] >= 10) {
      result[move + 1] += result[move] / 10;
      result[move] %= 10;
    }
  }
  while (result.size() && !result.back()) result.pop_back();
  return result;
}
vector<int> sub(vector<int> &vec1, vector<int> &vec2, bool isPrint = false) {
  vector<int> *big = &vec1, *less = &vec2;
  bool bigger = compare(vec1, vec2);
  if (!bigger) big = &vec2, less = &vec1;
  vector temp1 = *big, temp2 = *less;
  auto it1 = temp1.begin(), it2 = temp2.begin();
  while (it2 != temp2.end()) {
    if (*it1 >= *it2)
      *it1 -= *it2;
    else {
      *(it1 + 1) -= 1;
      *it1 = *it1 + 10 - *it2;
    }
    it1++;
    it2++;
  }
  while (temp1.size() && temp1.back() == 0) temp1.pop_back();
  return temp1;
}
vector<int> div(vector<int> vec1, vector<int> vec2) {
  if (!compare(vec1, vec2)) {
    return vector<int>{0};
  }
  vector<int> result(vec1.size() - vec2.size() + 1, 0);
  for (int i = vec1.size() - vec2.size(); i >= 0; i--) {
    int count = 0;
    vector<int> moveV(vec2.size() + i, 0);
    for (int j = i; j < moveV.size(); j++) {
      moveV[j] = vec2[j - i];
    }
    // cout<<1<<endl;
    while (compare(vec1, moveV)) {
      // cout<<2<<endl;
      count++;
      // cout<<"pre sub "<<endl;
      // printVector(vec1);
      vec1 = sub(vec1, moveV);
      // cout<<"after sub"<<endl;
      // printVector(vec1);
    }
    result[i] = count;
  }
  while (result.size() && !result.back()) result.pop_back();
  return result;
}
vector<int> mod(vector<int> vec1, vector<int> vec2) {
  vector<int> divv = div(vec1, vec2);
  auto mid = mul(divv, vec2);
  return sub(vec1, mid);
}
int main() {
  string temp;
  cin >> temp;
  length1 = temp.length();
  trans(temp, input1);

  cin >> temp;
  trans(temp, input2);
  length2 = temp.length();

  auto add = adding(input1, input2);
  printVector(add);

  auto subResult = sub(input1, input2);
  printVector(subResult);

  auto mulResult = mul(input1, input2);
  printVector(mulResult);

  auto divResult = div(input1, input2);
  printVector(divResult);

  auto midresult = mod(input1, input2);
  printVector(midresult);
  return 0;
}
