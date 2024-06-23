#include "fraction.hpp"
int Fraction::gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  if (a < b) return gcd(b, a);
  if (a == 1 || b == 1 || a == 0 || b == 0) {
    return 1;
  }
  int t = b;
  while ((a % b)) {
    t = a % b;
    a = b;
    b = t;
  }
  return t;
}
Fraction::Fraction(int a, int b) : molecule(a), denominator(b) {
  if (b == 0) {
    throw std::domain_error("divisor cannot be 0");
  }
  if (b < 0) {
    b = -b;
    a = -a;
  }
}

Fraction::Fraction(Fraction &other) : Fraction(other.molecule, other.denominator) {}
void Fraction::simplify() {
  int a;
  while ((a = gcd(molecule, denominator)) != 1) {
    denominator /= a;
    molecule /= a;
  }
}

inline bool Fraction::isNegative() { return ((denominator ^ molecule) >> 31) & 0x1; }
string Fraction::toString() {
  if (!molecule) return "0";
  return (isNegative() ? "-" : "") + to_string(abs(molecule)) + (denominator != 1 ? "/" + to_string(denominator) : "");
}

Fraction::Fraction(string &input) {
  // convert number to molecule / 10..0
  input.erase(input.begin(), find_if(input.begin(), input.end(), [&](auto &it) -> bool { return !isspace(it); }));
  molecule = denominator = 0;
  bool negativeTag = false;

  if (!input.empty() && input[0] == '-') {
    negativeTag = true;
    input.erase(input.begin());
  }

  denominator = pow(10, input.length() - 2);
  for (auto &it : input) {
    if (it != '.') {
      molecule = molecule * 10 + (it - '0');
    }
  }
  simplify();
  if (negativeTag) {
    molecule = -molecule;
  }
}

double Fraction::toDouble() { return 1.0 * molecule / denominator; }

string Fraction::toDoubleString(int digits) {
  stringstream stream;
  stream << std::fixed << setprecision(digits) << (1.0 * molecule / denominator);
  return stream.str();
}

ostream &operator<<(ostream &out, Fraction &f) {
  out << f.toString();
  return out;
}

istream &operator>>(istream &in, Fraction &f) {
  while (isspace(in.peek())) in.ignore();
  in >> f.molecule;
  while (isspace(in.peek())) in.ignore();
  if (in.peek() == '/') in.ignore();
  while (isspace(in.peek())) in.ignore();
  in >> f.denominator;
  if (f.denominator == 0) {
    throw std::domain_error("divisor cannot be 0");
  }
  f.simplify();
  return in;
}

Fraction Fraction::operator+(Fraction &other) {
  int a = (molecule), b = (denominator), c = (other.getMolecule()), d = (other.getDenominator());
  if (b != d) {
    int preB = b;
    int preD = d;
    a *= preD;
    b *= preD;
    c *= preB;
    d *= preB;
  }
  a += c;
  Fraction result(a, b);
  result.simplify();
  return result;
}

Fraction Fraction::operator-(Fraction &other) {
  int a = (molecule), b = (denominator), c = (other.getMolecule()), d = (other.getDenominator());
  if (b != d) {
    int preB = b;
    int preD = d;
    a *= preD;
    b *= preD;
    c *= preB;
    d *= preB;
  }
  a -= c;
  Fraction result(a, b);
  result.simplify();
  return result;
}

Fraction Fraction::operator*(Fraction &other) {
  int a = (molecule), b = (denominator), c = (other.getMolecule()), d = (other.getDenominator());
  a *= c;
  b *= d;
  Fraction result(a, b);
  result.simplify();
  return result;
}

Fraction Fraction::operator/(Fraction &other) {
  Fraction temp(other);
  if (temp.molecule == 0) {
    throw std::domain_error("divisor cannot be 0");
  }
  swap(temp.denominator, temp.molecule);
  if (temp.denominator < 0) {
    temp.denominator = -temp.denominator;
    temp.molecule = -temp.molecule;
  }
  return this->operator*(temp);
}

bool Fraction::operator<(Fraction &b) {
  int t1 = molecule * b.denominator;
  int t2 = denominator * b.molecule;
  if (isNegative()) {
    if (!b.isNegative()) return true;
    //都是负数,默认负数都在分子
    return t1 < t2;
  }
  if (b.isNegative()) {
    return false;
  }
  //都是正数
  return t1 < t2;
}

bool Fraction::operator==(Fraction &b) { return denominator == b.denominator && molecule == b.molecule; }
bool Fraction::operator<=(Fraction &b) { return this->operator<(b) || this->operator==(b); }
bool Fraction::operator!=(Fraction &b) { return !this->operator==(b); }
bool Fraction::operator>=(Fraction &b) { return !this->operator<(b); }
bool Fraction::operator>(Fraction &b) { return !this->operator<=(b); }