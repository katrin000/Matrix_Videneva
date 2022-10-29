#pragma once

#include <iostream>

using namespace std;

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size) : sz(size)
  {
    if (size <= 0) throw "TDynamicVector size<=0";
    sz = size;
    pMem = new T[size];

  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (s <= 0) throw "TDynamicVector size<=0";
    if (arr != nullptr) throw "TDynamicVector arr == nullptr";
    sz = s;
    pMem = new T[size];
    for (int i = 0; i < sz; i++)
      pMem[i] = arr[i];
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (&v == this) return *this;
    if (v.sz != sz) {
      T* tmpMem = new T[v.sz];
      delete[] pMem;
      sz = v.sz;
      pMem = tmpMem;
    }
    std::copy(v.pMem, v.pMem + sz, pMem);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz) throw out_of_range("elem pos is out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) throw out_of_range("elem pos is out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz) return false;
    for (size_t i = 0; i < sz; i++)
      if (pMem[i] != v.pMem[i]) return false;
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !operator==(v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      tmp.pMem[i] = pMem[i] + val;
    return tmp;
  }
  TDynamicVector operator-(T val)
  {
    return operator+(-val);
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++)
      tmp.pMem[i] = pMem[i] * val;
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) throw length_error("cant add vectors with not equal size");
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + v.pMem[i];
    return res;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
    return operator+(TDynamicVector(v) * (-1));
  }
  T operator*(const TDynamicVector& v)
  {
    if (sz != v.sz) throw length_error("cant multiply vectors with not equal size");
    T res{};
    for (size_t i = 0; i < sz; i++)
      res = res + pMem[i] * v.pMem[i];
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    ostr << "\n";
    return ostr;
  }
};
