#ifndef CELL_H
#define CELL_H

//#include "chip_graph.h"
#include "chip.h"

class Cell
{
public:
  Cell();
  Cell(Chip *chip, bool blocked);
  Chip* get_chip();
  void random_chip();
  bool is_blocked();
  ~Cell();
private:
  bool blocked;
  Chip *pointer_chip;
};

#endif // CELL_H
