#include "square_vector.h"

template<typename T>
make_2048::square_vector<T>::square_vector(unsigned int n)
{
  ksize_ = n;
  vec_.resize(ksize_);
  for (int i = 0; i < n; ++i)
    vec_[i].resize(n);
}

template<typename T>
const make_2048::uint_vec<T>& make_2048::square_vector<T>::operator [](size_t n) const
{
  if (0 > n || ksize_ <= n)
    throw std::out_of_range("class board_vec::operator[]::out of range");
  return vec_.at(n);
}

template<typename T>
make_2048::uint_vec<T>& make_2048::square_vector<T>::operator [](size_t n)
{
  if (0 > n || ksize_ <= n)
    throw std::out_of_range("class board_vec::operator[]::out of range");
  return vec_.at(n);
}

template<typename T>
void make_2048::square_vector<T>::resize(unsigned int &n)
{
  vec_.resize(n);
  for (int i = 0; i < n; ++i)
    vec_.at(i).resize(n);
}
