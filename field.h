#ifndef FIELD_H
#define FIELD_H

#include "cell.h"
#include <QStack>
#include <QVector>
#include <QWidget>
#include <QMessageBox>
#include <QGridLayout>
#include <QRgb>

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
  ~Field();

private:
  //логика
  Cell ***cell_matrix;
  size_t rows;
  size_t cols;
  QVector<Cell*> combination;
  void complete_combination();
  bool adjacency_check(Cell *added);

  //графика
  void createWindow();
  QGridLayout * grid;
  Cell ***cells;

private slots:
    void slotFromChip();
};


#endif // FIELD_H
