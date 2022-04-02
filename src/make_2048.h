#ifndef SRC_MAKE_2048_H
#define SRC_MAKE_2048_H

#include <cstdio>
#include <cstdlib>
#include <random>
#include <functional>

#include "square_vector.h"
#include "make_2048.h"
#include "../util/y0_conio.h"

namespace make_2048
{
  class make_2048
  {
    private:
      struct for_status
      {
        int border_i;
        int border_j;
        int init_i;
        int init_j;
        int delta_i;
        int delta_j;
      };

      enum {
        UP_,
        DOWN_,
        LEFT_,
        RIGHT_,
        MAX_DIRECTION
      };
      square_vector<unsigned int> board_;
      int krow_;
      int kcolumn_;

      // function
      void print_board();
      void swap_zero_and_not_zero(unsigned int &, unsigned int &);
      void set_x_y(bool, int **, int ** ,int * ,int *);
      bool keyboard_processing();
      bool move_panel_to_side(int);
      bool fusion_adjacent_direction(int);
      bool is_all_not_zero();
      bool is_complete();
      bool is_lose();
      bool is_out_of_range(const int &, const int &, const int &, const int &);
      for_status make_status_move_panel(int &);
      for_status make_status_fusion(int &);
      std::mt19937 generate_new_panel(std::mt19937);
      std::pair<std::function<bool(int, int)>, std::function<bool(int, int)> >
        get_function_if_expr(int &);
    public:
      make_2048(unsigned int);
      void make_2048_processing();
  };
} // namespace make_2048

#endif
