#ifndef FIELD_H
#define FIELD_H

#include "cell.h"
#include <QStack>
#include <QVector>
#include <QWidget>
#include <QMessageBox>
#include <QGridLayout>
#include <QRgb>
#include <QDebug>

class Field : public QWidget
{
  Q_OBJECT
public:
  explicit Field(QWidget *parent = 0, size_t rows = 0, size_t cols = 0);
  Cell* get_cell(size_t row, size_t col);
  bool check_cell(size_t row, size_t col);//проверяет наличие комбинаций с соседями
  void update_field();
  void random_field();
  void check_field();//проверяет наличие комбинаций на поле(шахматный порядок(чекнуть в случае с вырезами у краев))
  Cell* get_empty_cell(size_t temp_col, size_t& temp_row);
  Cell* get_not_empty_cell(size_t temp_col, size_t& temp_row);
  void add_to_combination(Cell* added);
  ~Field();

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
};


#endif // FIELD_H
