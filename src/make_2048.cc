#include "make_2048.h"

/*
 * fix_me:
 *  generate new number nontheless do not move
 */

make_2048::make_2048::make_2048(unsigned int n) 
{
  krow_    = n;
  kcolumn_ = n;
  board_.resize(n);
}

void make_2048::make_2048::make_2048_processing()
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  bool is_moved = true;

  while(1) {
    engine
      = is_moved ? generate_new_panel(engine) : engine;
    print_board();
    if (is_complete()) {
      printf("complete!!!!11!\n");
    }
    if (is_lose()) {
      printf("you lose...\n");
      break;
    }
    is_moved = keyboard_processing();
  }
}

bool make_2048::make_2048::keyboard_processing()
{
  bool is_moved = false;
  switch(getch()) {
    case 'w':
      is_moved  = move_panel_to_side(UP_);
      is_moved += fusion_adjacent_direction(UP_);
      break;
    case 's':
      is_moved  = move_panel_to_side(DOWN_);
      is_moved += fusion_adjacent_direction(DOWN_);
      break;
    case 'a':
      is_moved  = move_panel_to_side(LEFT_);
      is_moved += fusion_adjacent_direction(LEFT_);
      break;
    case 'd':
      is_moved  = move_panel_to_side(RIGHT_);
      is_moved += fusion_adjacent_direction(RIGHT_);
      break;
  }
  return is_moved;
}

make_2048::make_2048::for_status
make_2048::make_2048::make_status_move_panel(int &direction)
{
  for_status status;
  switch(direction) {
    case UP_:
      status = {kcolumn_, krow_, 0, 0, 1, 1};
      break;
    case DOWN_:
      status = {krow_, kcolumn_, krow_ - 1, kcolumn_ - 1, -1, -1};
      break;
    case LEFT_:
      status = {krow_, kcolumn_, 0, 0, 1, 1};
      break;
    case RIGHT_:
      status = {krow_, kcolumn_, 0, kcolumn_ - 1, 1, -1};
      break;
  }
  return status;
}

void make_2048::make_2048::set_x_y(
    bool is_up_or_down, int **x, int **y, int *i, int *j)
{
  if (is_up_or_down) {
    *x = i;
    *y = j;
  }
  else {
    *x = j;
    *y = i;
  }
}

bool make_2048::make_2048::move_panel_to_side(int direction)
{
  auto expr_if = get_function_if_expr(direction);
  for_status status = make_status_move_panel(direction);
  bool is_up_or_down = (UP_ == direction || DOWN_ == direction);
  bool is_moved = false;

  for (int i = status.init_i;
      expr_if.first(i, status.border_i); i += status.delta_i) {
    for (int j = status.init_j;
        expr_if.second(j, status.border_j); j += status.delta_j) {
      int *y, *x; 
      int point;
      set_x_y(is_up_or_down, &x, &y, &i, &j);
      point = j;
      if (board_[*y][*x])
        continue;
      if (is_up_or_down) *y += status.delta_j;
      else *x += status.delta_j;
      for (int k = (is_up_or_down ? *y : *x);
          expr_if.second(k, status.border_j); k += status.delta_j) {
        if (is_up_or_down) {
          if (!board_[k][*x])
            continue;
          swap_zero_and_not_zero(board_[k][i], board_[point][i]);
          is_moved = true;
          *y = point;
          break;
        }
        else {
          if (!board_[*y][k])
            continue;
          swap_zero_and_not_zero(board_[*y][k], board_[*y][point]);
          is_moved = true;
          *x = point;
          break;
        }
      }
    }
  }
  return is_moved;
}

std::pair<std::function<bool(int, int)>, std::function<bool(int, int)> >
make_2048::make_2048::get_function_if_expr(int &direction)
{
  auto value_less_than_border
    = [](int value, int border){return value < border;};
  auto value_gereater_than_or_equal_border
    = [](int value, int border){return 0 <= value;};
  switch (direction) {
    case UP_:
      return std::make_pair(value_less_than_border, value_less_than_border);
    case DOWN_:
      return std::make_pair(
          value_gereater_than_or_equal_border, value_gereater_than_or_equal_border);
    case LEFT_:
      return std::make_pair(value_less_than_border, value_less_than_border);
    case RIGHT_:
      return std::make_pair(
          value_less_than_border, value_gereater_than_or_equal_border);
  }
}

make_2048::make_2048::
for_status make_2048::make_2048::make_status_fusion(int &direction)
{
  for_status status;
  switch(direction) {
    case UP_:
      status = {kcolumn_, krow_, 0, 1, 1, 1};
      return status;
    case DOWN_:
      status
        = {kcolumn_, krow_, kcolumn_ - 1, krow_ - 2, -1, -1};
      return status;
    case LEFT_:
      status = {krow_, kcolumn_, 0, 1, 1, 1};
      return status;
    case RIGHT_:
      status = {krow_, kcolumn_, 0, kcolumn_ - 2, 1, -1};
      return status;
  }
}

bool make_2048::
make_2048::fusion_adjacent_direction(int direction)
{
  auto expr_if = get_function_if_expr(direction);
  bool is_up_or_down = (UP_ == direction || DOWN_ == direction);
  bool is_fusion = false;
  for_status status = make_status_fusion(direction);
  int offset_y = (UP_   == direction ? -1 : (DOWN_  == direction ? 1 : 0));
  int offset_x = (LEFT_ == direction ? -1 : (RIGHT_ == direction ? 1 : 0));

  for (int i = status.init_i; expr_if.first(i, krow_); i += status.delta_i) {
    for (int j = status.init_j; expr_if.second(j, kcolumn_); j += status.delta_j) {
      int *x, *y;
      set_x_y(is_up_or_down, &x, &y, &i, &j);
      if (board_[*y][*x] != board_[*y + offset_y][*x + offset_x])
        continue;
      if (!board_[*y][*x])
        continue;
      board_[*y + offset_y][*x + offset_x] *= 2;
      board_[*y][*x] = 0;
      is_fusion = true;
    }
  }
  move_panel_to_side(direction);
  return is_fusion;
}

void make_2048::make_2048::swap_zero_and_not_zero(
  unsigned int &value_1, unsigned int &value_2)
{
  int value = value_1;
  value_1 = value_2;
  value_2 = value;
}

std::mt19937 make_2048::make_2048::generate_new_panel(std::mt19937 engine)
{
  while(1) {
    auto row    = engine() % krow_;
    auto column = engine() % kcolumn_;
    if (is_all_not_zero())
      return engine;
    if (board_[row][column])
      continue;
    board_[row][column] = engine() % 2 ? 4 : 2;
    return engine;
  }
}

bool make_2048::make_2048::is_all_not_zero()
{
  for (int i = 0; i < krow_; ++i)
    for (int j = 0; j < kcolumn_; ++j)
      if (!board_[i][j])
        return false;
  return true;
}

void make_2048::make_2048::print_board()
{
  std::system("clear");
  printf("+----+----+----+----+----+\n");
  for (size_t i = 0; i < krow_; ++i) {
    printf("|");
    for (size_t j = 0; j < kcolumn_; ++j) {
      if (board_[i][j])
        printf("%4d|", board_[i][j]);
      else
        printf("%4c|", ' ');
    }
    printf("\n+----+----+----+----+----+\n");
  }
}

bool make_2048::make_2048::is_complete()
{
  for (int i = 0; i < krow_; ++i)
    for (int j = 0; j < kcolumn_; ++j)
      if (2048 <= board_[i][j])
        return true;
  return false;
}

bool make_2048::make_2048::is_lose()
{
  for (int i = 0; i < krow_; ++i)
    for (int j = 0; j < kcolumn_; ++j)
      for (int k = -1; k < 2; ++k)
        for (int l = -1; l < 2; ++l) {
          if (!board_[i][j])
            return false;
          if (abs(k) == abs(l))
            continue;
          if (is_out_of_range(i, j, k, l))
            continue;
          if (board_[i][j] == board_[i + k][j + l])
            return false;
        }
  return true;
}

bool make_2048::make_2048::is_out_of_range(
  const int &i, const int &j, const int &k, const int &l)  
{
  return (0 > i + k || 0 > j + l
    || krow_ - 1 < i + k || kcolumn_ - 1 < j + l);
}
