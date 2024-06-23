#include "Vector.hpp"
using namespace std;
template <class T>
Vector<T>::Vector() {
  m_nSize = 0;
  m_nCapacity = 20;
  m_pElements = new T[m_nCapacity];
}

template <class T>
Vector<T>::Vector(int size) {
  m_nCapacity = size;
  m_nSize = 0;
  m_pElements = new T[size];
}

template <class T>
Vector<T>::Vector(const Vector &r) : m_nSize(r.m_nSize), m_nCapacity(r.m_nCapacity) {
  m_pElements = new T[m_nCapacity];
  copy(r.m_pElements, r.m_pElements + r.m_nSize, m_pElements);
}

template <class T>
Vector<T>::~Vector() {
  delete[] m_pElements;
}

template <class T>
T &Vector<T>::operator[](int index) {
  return m_pElements[index];
}

template <class T>
T &Vector<T>::at(int index) {
  if (index >= m_nSize || index < 0) {
    throw std::out_of_range("out_of_range");
  }
  return m_pElements[index];
}

template <class T>
int Vector<T>::size() const {
  return m_nSize;
}

template <class T>
void Vector<T>::push_back(const T &t) {
  if (m_nSize == m_nCapacity) {
    inflate();
  }
  m_pElements[m_nSize++] = t;
}

template <class T>
void Vector<T>::clear() {
  m_nSize = 0;
}

template <class T>
bool Vector<T>::empty() const {
  return m_nSize == 0;
}

template <class T>
void Vector<T>::inflate() {
  auto temp = new T[2 * m_nCapacity];
  copy(m_pElements, m_pElements + m_nSize, temp);
  delete m_pElements;
  m_pElements = temp;
  m_nCapacity *= 2;
}
