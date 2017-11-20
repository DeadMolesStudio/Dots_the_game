#include "chip.h"
#include <cstdlib>

Chip::Chip()
{
    //TODO: все это надо подгружать из конфига файла
    QTime time(0, 0, 0);
    qsrand(time.secsTo(QTime::currentTime()) * rand());
    shape = 1; //тоже генератор
    color = qrand() % 5; //случайный цвет из 5и возможных
    points = shape * 5;
}

Chip::Chip(int shape, int color) :
    shape(shape), color(color)
{
    points = shape * 5;
}

