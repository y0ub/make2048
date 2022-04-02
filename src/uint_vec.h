#ifndef SRC_BOARD_VEC_H
#define SRC_BOARD_VEC_H

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

#endif
