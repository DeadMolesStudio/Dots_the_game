#ifndef CHIP_H
#define CHIP_H

#include <QTime>

struct Chip
{
  Chip();//points заполняется в зависимости от shape
  Chip(const Chip &other);
  Chip(int shape, int color);

  int shape;
  int color;
  int points;
};

#endif // CHIP_H
