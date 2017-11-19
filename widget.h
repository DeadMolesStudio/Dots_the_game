#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QGridLayout>

//#include "level.h"

#include "cell.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void createGridForChips();
    QGraphicsScene  *scene;     // Объявляем графическую сцену
    QGridLayout * grid;
    Cell ***cells;

private slots:
    void slotFromChip();
};

#endif // WIDGET_H
