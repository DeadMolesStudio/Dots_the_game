#ifndef CELL_H
#define CELL_H

#include <chip.h>
#include <QWidget>
#include <QPainter>

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
protected:
  void mousePressEvent(QMouseEvent *event);

private:
  bool blocked;
  Chip *pointer_chip;

  //QRectF boundingRect() const;


signals:
    void signal1();
};

#endif // CELL_H
