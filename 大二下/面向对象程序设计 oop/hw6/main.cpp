#include <iostream>
#include "Vector.cpp"
int main() {
  Vector<int> a(10);
  std::cout << "a's size is " << a.size() << std::endl;
  for (int i = 0; i < 20; i++) {
    a.push_back(i);
  }
  std::cout << "after inflate a's size is " << a.size() << std::endl;
  puts("");
  for (int i = 0; i < a.size(); i++) {
    std::cout << "a[" << i << "] is " << a[i] << std::endl;
    std::cout << "a.at(" << i << ") is " << a.at(i) << std::endl;
  }
  puts("");
  std::cout << "if we try to catch a.at(a.size()), it should throw a exception\n";
  try {
    a.at(a.size());
  } catch (out_of_range msg) {
    std::cerr << "exception! ";
    std::cerr << msg.what() << std::endl;
    puts("");
  }
  std::cout << "using copy constructor to build new Vector n" << std::endl;
  Vector<int> n(a);
  std::cout << "value store in n should be the same as a \n";
  for (int i = 0; i < n.size(); i++) {
    std::cout << "n[" << i << "] is " << n[i] << std::endl;
    std::cout << "n.at(" << i << ") is " << n.at(i) << std::endl;
  }
  puts("");
  std::cout << "n is empty ? " << (n.empty() ? "true" : "false") << std::endl;
  n.clear();
  std::cout << "after n.clear(), n is empty ? " << (n.empty() ? "true" : "false") << std::endl;
  return 0;
}
