#include "chip.h"
#include <cstdlib>

Chip::Chip()
{
    //TODO: все это надо подгружать из конфига файла
    QTime time(0, 0, 0);
    qsrand(time.secsTo(QTime::currentTime()) * rand());
    int chance = 7;
    int temp = qrand() % chance;
    shape = (temp < chance - 1) ? 0 : 1; //тоже генератор
    qsrand(time.secsTo(QTime::currentTime()) * rand());
    color = qrand() % 5; //случайный цвет из 5и возможных
    points = (1 + shape) * 5;
}

Chip::Chip(int shape, int color) :
    shape(shape), color(color)
{
    points = (1 + shape) * 5;
}

