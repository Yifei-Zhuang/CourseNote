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
  if (a.size() < b.size()) {
    // cout<<"result is false1\n";
    return false;
  } else if (a.size() > b.size()) {
    // cout<<"result is true1\n";
    return true;
  }

  else {
    auto it1 = a.crbegin(), it2 = b.crbegin();
    while (it1 != a.crend()) {
      if (*it1 > *it2)
        return true;
      else if (*it1 < *it2) {
        // cout<<"result is false2\n";
        return false;
      }
      it1++;
      it2++;
    }
    // cout<<"result is true2\n";
    return true;
  }
}
// 一个写的比较辣鸡的add函数

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
  //   printVector(temp1);
  while (temp1.size() && temp1.back() == 0) temp1.pop_back();
  return temp1;
}
vector<int> div(vector<int> vec1, vector<int> vec2) {
  if (!compare(vec1, vec2)) {
    return vector<int>(1, 0);
  }
  vector<int> result(vec1.size() - vec2.size() + 1, 0);
  for (int i = vec1.size() - vec2.size(); i >= 0; i--) {
    int count = 0;
    vector<int> moveV(vec2.size() + i, 0);
    for (int j = i; j < moveV.size(); j++) {
      moveV[j] = vec2[j - i];
    }
    while (compare(vec1, moveV)) {
      count++;
      vec1 = sub(vec1, moveV);
    }
    if (count > 10) throw runtime_error("???");
    ;
    result[i] = count;
  }
  while (result.size() && !result.back()) result.pop_back();

  return result;
}
vector<int> mod(vector<int> vec1, vector<int> vec2) {
  if (!compare(vec1, vec2)) return vec1;
  vector<int> divv = div(vec1, vec2);
  //   printVector(divv);
  auto mid = mul(divv, vec2);
  // printVector(mid);
  return sub(vec1, mid);
}
int vec2int(vector<int> &vec) {
  int result = 0;
  for (int i = vec.size() - 1; i >= 0; i--) {
    result *= 10;
    result += vec[i];
  }
  return result;
}
int main() {
  string line;
  vector<int> p, g, pa, pb;  // 表示p g a私钥，b私钥
  cin >> line, trans(line, p);
  cin >> line, trans(line, g);
  cin >> line, trans(line, pa);
  cin >> line, trans(line, pb);
  vector<int> publicA, publicB, sKey;

  publicA = g;
  int times = vec2int(pa);
  for (int i = 1; i < times; i++) {
    publicA = mul(publicA, g);
  }
  publicA = mod(publicA, p);
  printVector(publicA);

  publicB = g;
  times = vec2int(pb);
  for (int i = 1; i < times; i++) {
    publicB = mul(publicB, g);
  }
  publicB = mod(publicB, p);
  printVector(publicB);

  sKey = publicA;
  times = vec2int(pb);
  for (int i = 1; i < times; i++) {
    sKey = mul(sKey, publicA);
  }
  sKey = mod(sKey, p);
  printVector(sKey);

  return 0;
}

// 353
// 3
// 97
// 233
