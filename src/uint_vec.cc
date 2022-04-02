#include "uint_vec.h"

template<typename T>
const T& make_2048::uint_vec<T>::operator[](size_t n) const
{
  if (0 > n || column_.size() <= n)
    throw std::out_of_range("class uint_vec::operator[]::out of range");
  return column_.at(n);
}

template<typename T>
T& make_2048::uint_vec<T>::operator[](size_t n)
{
  if (0 > n || column_.size() <= n)
    throw std::out_of_range("class uint_vec::operator[]::out of range");
  return column_.at(n);
}

template<typename T>
void make_2048::uint_vec<T>::resize(T &n)
{
  column_.resize(n);
}
