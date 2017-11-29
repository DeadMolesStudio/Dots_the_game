#ifndef LEVEL_H
#define LEVEL_H

#include "field.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QPalette>

class Level : public QWidget
{
      Q_OBJECT
public:
  Level(QWidget *parent = 0, int max_moves = 10, size_t rows = 6, size_t cols = 6);
  //void check_reqs(Cell* cell);
  //TODO:pause  ?
  //TODO:start  ?
  //TODO:stop ?
  ~Level();

  //графика
  void createLevelWindow();

private:
  Field *field;
  unsigned int score;
  int max_moves;
  int cur_moves;

  //QVector<Requirement> reqs;

  //графика
  QGridLayout *grid;
  QTextEdit *score_text;

private slots:
  void update_score_Slot(unsigned int add_score);

};

#endif // LEVEL_H
