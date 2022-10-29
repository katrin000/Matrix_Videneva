#pragma once

#include <iostream>
#include "vector.cpp"

using namespace std;

template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  //using TDynamicVector<TDynamicVector<T>>::pMem;
  //using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t size = 1) : TDynamicVector<TDynamicVector<T>>(size)
  {
    if (size <= 0) throw "Error: dynamicMarix size <= 0";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {}

  //using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  //bool operator==(const TDynamicMatrix& m) const noexcept
  //{
  //    return TDynamicVector<TDynamicVector<T> == m;
  //}

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * val;
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()) throw length_error("cant multiply matrix and vector with not equal size");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * v;
    return res;
  }

  // матрично-матричные операции
  //TDynamicMatrix operator+(const TDynamicMatrix& m)
  //{
  //}
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    return TDynamicVector<TDynamicVector<T>>::operator+(TDynamicMatrix(m) * (-1));
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw length_error("cant multiply matrixs with not equal size");
    TDynamicMatrix<T> res(sz);
    T tmp{};
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++) {
        tmp = T{};
        for (size_t k = 0; k < sz; k++)
          tmp = tmp + pMem[i][k] * m.pMem[k][j];
        res[i][j] = tmp;
      }
    return res;
  }

  //// ввод/вывод
  //friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  //{
  //}
  //friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  //{
  //}
};