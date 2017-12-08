#ifndef LEVEL_H
#define LEVEL_H

#include "field.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QPalette>
#include <QVector>
#include "requirement.h"
#include "reqset.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSpacerItem>
#include <QTextEdit>
#include <QPropertyAnimation>
#include "bonuses.h"

class Level : public QWidget
{
      Q_OBJECT
public:
  Level(QWidget *parent = 0, int max_moves = 10, size_t rows = 6, size_t cols = 6);
  //TODO:pause  ?
  //TODO:start  ?
  //TODO:stop ?
  ~Level();

  //графика
  void createLevelWindow();

private:
  ReqSet *reqset;
  Field *field;
  Bonuses *bonuses;
  unsigned int score;
  unsigned int winscore;
  int max_moves;
  int cur_moves;
  bool reqs_done;

  QVector<Requirement> reqs;

  //графика
  QGridLayout *grid;
  QGridLayout *info;
  QVector<QTextEdit *> text;

private slots:
  void update_score_Slot(unsigned int add_score);
  void check_reqs_Slot(Chip test);
  void quants_SLOT(int color);

signals:
  void update_reqs_info(QVector<Requirement> reqs);
  void quants_SIGNAL(int color);

};

#endif // LEVEL_H
