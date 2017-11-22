#ifndef CELL_H
#define CELL_H

#include <chip.h>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QMessageBox>
#include <QColor>
#include <QRgb>

class Cell : public QWidget
{
    Q_OBJECT
public:
  Cell(QWidget *parent = 0);
  Cell(Chip *chip, bool blocked);
  Chip* get_chip();
  void random_chip();
  bool is_blocked();
  ~Cell();

  void paintEvent(QPaintEvent *event);
  void activate();
  void deactivate();

protected:
  void mousePressEvent(QMouseEvent *event);
  void update_chip_model(QPainter *painter);
  void activate_graphics(QPainter *painter);
  void deactivate_graphics(QPainter *painter);

private:
  bool blocked;
  Chip *pointer_chip;

  //QRectF boundingRect() const;
  bool in_combination;
  //QPainter cell_painter;

signals:
    void signal1();
};

#endif // CELL_H
