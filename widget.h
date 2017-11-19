#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

//#include "level.h"
#include "chip_graph.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     // Объявляем графическую сцену
    //Level *level;
    Chip_graph **chip;
};

#endif // WIDGET_H
