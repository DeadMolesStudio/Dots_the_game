#include "level.h"


Level::Level()
    : field(0, 5, 5)
{
    max_moves = 10;
    cur_moves = 0;
    score = 0;
    //field = Field(0, 5, 5);
}

Level::Level(int max_moves, size_t rows, size_t cols) :
     field(0, rows, cols), score(0), max_moves(max_moves), cur_moves(0)
{
    //field = Field(0, rows, cols);
}
