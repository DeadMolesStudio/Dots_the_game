#ifndef LEVEL_H
#define LEVEL_H

#include "field.h"

class Level
{
public:
  Level();
  Level(int max_moves, size_t rows, size_t cols);
  Field& get_field();
  //void check_reqs(Cell* cell);
  //TODO:pause  ?
  //TODO:start  ?
  //TODO:stop ?
  ~Level();

private:
  Field field;
  unsigned int score;
  int max_moves;
  int cur_moves;
  //QVector<Requirement> reqs;
};

#endif // LEVEL_H
