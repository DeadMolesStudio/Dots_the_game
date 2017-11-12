#include "boost или stl или еще шо то.h"
class Level
{
public:
  Level();
  Level()
  void check_reqs(Cell* cell);
  //TODO:pause  ?
  //TODO:start  ?
  //TODO:stop ?
  ~Level();
private:
  Field field;
  unsigned int score;
  int max_moves;
  int cur_moves;
  std::vector<Requirement> reqs;
}

class Field
{
public:
  Field();
  Cell& get_cell(size_t col, size_t row);
  void update_field();
  void random_field();
  void check_field();//проверяет наличие комбинаций на поле(шахматный порядок(чекнуть в случае с вырезами у краев))
  Cell* get_empty_cell(size_t temp_col, size_t& temp_row);
  Cell* get_not_empty_cell(size_t temp_col, size_t& temp_row);
  void start_combination(Cell *first);
  ~Field();
private:
  Cell **cell_matrix;
  size_t rows;
  size_t cols;
  stack<Cell*> combination;//TODO:откуда будем брать стэк?
}

class Cell
{
public:
  Cell();
  Chip* get_chip();
  void random_chip();
  bool check_cell();//проверяет наличие комбинаций с соседями
  bool is_blocked();
  ~Cell();
private:
  bool blocked;
  Chip *pointer_chip;
}

struct Chip
{
  Chip();//points заполняется в зависимости от shape

  int shape;
  int color;
  int points;
}

struct Requirement
