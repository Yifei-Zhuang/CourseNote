#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

class Fraction {
 public:
  Fraction() = default;
  Fraction(int a, int b);
  Fraction(Fraction &other);
  Fraction(string &input);
  inline string toString();
  double toDouble();
  string toDoubleString(int digits);
  friend ostream &operator<<(ostream &out, Fraction &f);
  friend istream &operator>>(istream &in, Fraction &f);
  Fraction operator+(Fraction &b);
  Fraction operator-(Fraction &b);
  Fraction operator*(Fraction &b);
  Fraction operator/(Fraction &b);
  bool operator<(Fraction &b);
  bool operator<=(Fraction &b);
  bool operator==(Fraction &b);
  bool operator!=(Fraction &b);
  bool operator>=(Fraction &b);
  bool operator>(Fraction &b);
  inline int getMolecule() { return molecule; }
  inline int getDenominator() { return denominator; }

 private:
  int gcd(int a, int b);
  void simplify();
  inline bool isNegative();
  int molecule{0}, denominator{1};
};
