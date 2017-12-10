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
#include "line_selecter.h"
#include "selecter.h"
#include <QPushButton>

class Level : public QWidget
{
      Q_OBJECT
public:
  Level(QWidget *parent = 0, int max_moves = 10, size_t rows = 6, size_t cols = 6);
  Selecter *selecter;
  Line_selecter *line_selecter;
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
  QPushButton *menu;

private slots:
  void update_score_Slot(unsigned int add_score);
  void check_reqs_Slot(Chip test);
  void quants_SLOT(int color);
  void show_selecter();
  void start_bonus(int bonus);
  void hide_line_selecter(size_t number);
  void to_menu();


signals:
  void update_reqs_info(QVector<Requirement> reqs);
  void quants_SIGNAL(int color);

  void line_bonus_SIGNAL();
  void random_bonus_SIGNAL();
  void color_bonus_SIGNAL();

  void show_selecter_SIGNAL(bool need_to_show);
  void choosed_line_SIGNAL(size_t number);
  void add_req_SIGNAL(Requirement added);

  void enable_preset1();
  void enable_preset2();
  void enable_preset3();

  void to_menu_SIGNAL();
  void clear_me();

public slots:
  void add_req(int shape, int color, size_t demand);
  void level1();
  void level2();
  void level3();
  void choosed_level(uint number);
  void add_move();

};

#endif // LEVEL_H
