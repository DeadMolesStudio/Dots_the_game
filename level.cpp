#include "level.h"


Level::Level()
{
    max_moves = 10;
    cur_moves = 0;
    score = 0;
    field = Field(5, 5);
}

Level::Level(int max_moves, size_t rows, size_t cols) :
     score(0), max_moves(max_moves), cur_moves(0)
{
    field = Field(rows, cols);
}
