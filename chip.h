#ifndef CHIP_H
#define CHIP_H

#include <QTime>
//#include <QColor>
//#include <QVector>

//enum color_set{
//    yellow,
//    green,
//    blue,
//    red,
//    purple
//};

//QVector<QColor> my_colors;

//my_colors.push_back(QColor(157,129,186,255));
//my_colors.push_back(QColor(255,255,82,255));
//my_colors.push_back(QColor(0,255,127,255));
//my_colors.push_back(QColor(0,65,106,255));
//my_colors.push_back(QColor(197,29,52,255));

struct Chip
{
  Chip();//points заполняется в зависимости от shape
  Chip(int shape, int color);

  int shape;
  int color;
  int points;
};

#endif // CHIP_H
