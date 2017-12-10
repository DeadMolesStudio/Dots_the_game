#ifndef CELL_H
#define CELL_H

#include <chip.h>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QMessageBox>
#include <QColor>
#include <QRgb>
#include <QMouseEvent>
#include <QLine>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>

enum class Chip_colors {
    Yellow = 0xffff99,
    Green = 0xffc8a8,
    Dark_blue = 0x9370d8,
    Red = 0xfc6c85,
    Purple = 0xea8df7
};

class Cell : public QWidget
{
  Q_OBJECT
public:
  Cell(QWidget *parent = 0);
  Cell(QWidget *parent, Chip chip, bool blocked);
  Chip* get_chip();
  void animated_random_chip();
  bool is_blocked();
  bool is_in_combination();
  bool is_in_quadr();
  void set_quadr_flag(bool value);
  ~Cell();


  void paintEvent(QPaintEvent *event);
  void activate();
  void deactivate();
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
//  void mouseReleaseEvent(QMouseEvent *event);
//  void mousePressEvent(QMouseEvent *event);

protected:
  void mouseReleaseEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void update_chip_model(QPainter *painter);
  void activate_graphics(QPainter *painter);
  void deactivate_graphics(QPainter *painter);
  void drawTriangle(QPainter *painter);
  void drawChip(QPainter *painter);

private:
  bool blocked;
  bool destroing;
  Chip *pointer_chip;

  //QRectF boundingRect() const;
  bool in_combination;
  bool in_quadr;
  int current_radius;

  //QPainter cell_painter;

signals:
  //void signal1();
  void pressSignal();
  void enterSignal();
  void leaveSignal();
  void releaseSignal();
  void moveSignal(QPoint mouse_pos);

private slots:
  //void drawTriangle_by_size(QPainter *painter, int size);
  void update_by_radius(int radius);
  void smaller();
  void bigger();
  void set_small();
  void set_big();
  void get_small();
  void get_big();
  void random_chip();

public slots:
  void block(bool blocked);

};

#endif // CELL_H
