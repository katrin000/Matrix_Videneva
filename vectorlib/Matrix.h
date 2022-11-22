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

  // ñðàâíåíèå
  //bool operator==(const TDynamicMatrix& m) const noexcept
  //{
  //    return TDynamicVector<TDynamicVector<T> == m;
  //}

  // ìàòðè÷íî-ñêàëÿðíûå îïåðàöèè
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * val;
    return res;
  }

  // ìàòðè÷íî-âåêòîðíûå îïåðàöèè
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()) throw length_error("cant multiply matrix and vector with not equal size");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * v;
    return res;
  }

  // ìàòðè÷íî-ìàòðè÷íûå îïåðàöèè
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

  //// ââîä/âûâîä
  //friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  //{
  //}
  //friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  //{
  //}
};
// Верхнетреугольная матрица
template <typename T>
class TDynamicMatrix : public TDynamicVector < TDynamicVector<T >
{
public:
  TDynamicMatrix(int s = 10);
  TDynamicMatrix<T>(const TDynamicMatrix& mt);                    // копирование
  TDynamicMatrix<T>(const TDynamicVector<TDynamicVector<T> >& mt); // преобразование типа
  bool operator==(const TDynamicMatrix& mt) const;      // сравнение
  bool operator!=(const TDynamicMatrix& mt) const;      // сравнение
  TDynamicMatrix& operator= (const TDynamicMatrix& mt);        // присваивание
  TDynamicMatrix  operator+ (const TDynamicMatrix& mt);        // сложение
  TDynamicMatrix  operator- (const TDynamicMatrix& mt);        // вычитание
  TDynamicMatrix  operator* (const TDynamicMatrix& mt);
  // ввод / вывод
  friend istream& operator>>(istream& in, TDynamicMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream& out, const TDynamicMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
}

template <class T>
TDynamicMatrix< T>::TDynamicMatrix(int s) : TDynamicVector<TDynamicVector< T>>(s)
{
  if ((s < 1) || (s > MAX_MATRIX_SIZE))
    throw string("Wrong argument");
  for (int i = 0; i < s; i++) {
    TDynamicVector<T> tmp(s - i, i);
    this->pVector[i] = tmp;
  }
}
template <class T> // конструктор копирования
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& mt) :
  TDynamicVector<TDynamicVector<T> >(mt) {}

template <class T> // конструктор преобразования типа
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicVector<TDynamicVector<T> >& mt) :
  TDynamicVector<TDynamicVector<T> >(mt) {}

template <class T> // сравнение
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& mt) const
{
  return TDynamicVector<TDynamicVector<T>>:: operator==(mt);
}

template <class T> // сравнение
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& mt) const
{
  return !(*this == mt);
}

template <class T> // присваивание
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& mt)
{
  if (this == &mt)
    return *this;
  TDynamicVector<T>* tmp = new TDynamicVector<T>[mt.Size];
  delete[] this->pVector;
  this->pVector = tmp;
  this->Size = mt.Size;
  for (int i = 0; i < this->Size; i++) {
    this->pVector[i] = mt.pVector[i];
  }
  return *this;
}

template <class T> // сложение
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& mt)
{
  return TDynamicVector<TDynamicVector<T>>:: operator+(mt);
}

template <class T> // вычитание
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& mt)
{
  return TDynamicVector<TDynamicVector<T>>:: operator-(mt);
}

