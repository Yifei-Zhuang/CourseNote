#include "fraction.hpp"
int main() {
  Fraction a;
  string input;
  cout << "input a in format like 3 / 4" << endl;
  try {
    cin >> a;
  } catch (exception e) {
    cerr << e.what() << endl;
  }
  cout << "input b in a string format like 1.2" << endl;
  cin >> input;
  Fraction b(input);
  cout << "a is " << setw(8) << left << a.toDouble() << "\nb is " << setw(8) << left << b.toDouble() << endl;
  auto add = a + b;
  cout << "arithmetical:" << endl;
  cout << "a + b is " << setw(8) << left << add << endl;
  auto sub = a - b;
  cout << "a - b is " << setw(8) << left << sub << endl;
  auto mul = a * b;
  cout << "a * b is " << setw(8) << left << mul << endl;
  try {
    auto div = a / b;
    cout << "a / b is " << setw(8) << left << div << endl;
  } catch (domain_error e) {
    cerr << "a / b :" << e.what() << endl;
  }
  cout << "relational:" << endl;
  cout << "a <  b is " << setw(8) << left << (a < b ? "true" : "false") << endl;
  cout << "a <= b is " << setw(8) << left << (a <= b ? "true" : "false") << endl;
  cout << "a == b is " << setw(8) << left << (a == b ? "true" : "false") << endl;
  cout << "a != b is " << setw(8) << left << (a != b ? "true" : "false") << endl;
  cout << "a >= b is " << setw(8) << left << (a >= b ? "true" : "false") << endl;
  cout << "a >  b is " << setw(8) << left << (a > b ? "true" : "false") << endl;
  cout << "cast:" << endl;
  cout << "cast a to double " << setw(8) << left << a.toDouble() << endl;
  cout << "cast b to double string in 3 precision " << setw(8) << left << b.toDoubleString(3) << endl;
  return 0;
}