#include "chip.h"
#include <cstdlib>

Chip::Chip()
{
    shape = std::rand() % 1;
    color = std::rand() % 5; //случайный цвет из 5и возможных
    points = shape * 5;
}

Chip::Chip(int shape, int color) :
    shape(shape), color(color)
{
    points = shape * 5;//TODO:читать из конфига или еще откуда то
}
