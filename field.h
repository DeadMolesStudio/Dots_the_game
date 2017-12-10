#ifndef FIELD_H
#define FIELD_H

#include "cell.h"
#include <QStack>
#include <QVector>
#include <QWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGridLayout>
#include <QRgb>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

class Field : public QWidget
{
  Q_OBJECT
public:
  explicit Field(QWidget *parent = 0, size_t rows = 0, size_t cols = 0);
  Cell* get_cell(size_t row, size_t col);
  bool cell_position(Cell *cell, size_t &row, size_t &col);
  bool check_cell(size_t row, size_t col);//проверяет наличие комбинаций с соседями
  void random_field();
  void update_field();
  void check_field();//проверяет наличие комбинаций на поле(шахматный порядок(чекнуть в случае с вырезами у краев))
  Cell* get_empty_cell(size_t temp_col, size_t& temp_row);
  Cell* get_not_empty_cell(size_t temp_col, size_t& temp_row);
  void add_to_combination(Cell* added);
  ~Field();

public slots:
  void random_field_bonus();
  void line_destroy_bonus(size_t number);
  void color_bonus();
  void set_cell_blocked(size_t row, size_t col);

  void preset1();
  void preset2();
  void preset3();

private:
  //логика
  Cell ***cell_matrix;
  size_t rows;
  size_t cols;
  QVector<Cell*> combination;
  void complete_combination();
  void complete_quadr_combination();
  bool adjacency_check(Cell *added);
  void repaint_field();
  unsigned int quadr();
  unsigned int quant();

  //графика
  void createWindow();
  QGridLayout * grid;
  Cell ***cells;

private slots:
  //void slotFromChip();
  void pressSlot();
  void releaseSlot();
  void moveSlot(QPoint mouse_pos);

signals:
  void plusScore(unsigned int add_score);
  void check_reqs_for_cell(Chip test);
  void quant_s(int color);
  void not_quant();
  void add_extra_move();
};


#endif // FIELD_H
