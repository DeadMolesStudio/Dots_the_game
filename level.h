#ifndef LEVEL_H
#define LEVEL_H

#include "field.h"

class Level
{
public:
  Level();
  Level(QString filename);
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
