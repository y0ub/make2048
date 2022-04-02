#ifndef SRC_SQUARE_VECTOR_H
#define SRC_SQUARE_VECTOR_H

#include <stdexcept>
#include <vector>

/*
 * todo: make no arguments constructor 
 */
namespace make_2048
{
  template<typename T>
  class uint_vec
  {
    private:
      std::vector<T> column_;

    public:
      const T& operator[](size_t) const;
      T& operator[](size_t);
      void resize(T &);
  };
} // make_2048

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

namespace make_2048
{
  template<typename T>
  class square_vector
  {
    private:
      std::vector<uint_vec<T> > vec_;
      unsigned int ksize_;

    public:
      square_vector(){};
      square_vector(unsigned int);
      const uint_vec<T>& operator[](size_t n) const;
      uint_vec<T>& operator[](size_t n);
      void resize(unsigned int &);
  };
} // namespace make_2048

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

#endif
