#ifndef CHIP_H
#define CHIP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>

// Наследуемся от QGraphicsItem
class Chip_graph : public QGraphicsItem
{
public:
    Chip_graph();
    ~Chip_graph();
    void click();
protected:
    QRectF boundingRect() const;    /* Определяем виртуальный метод,
                                     * который возвращает область, в которой
                                     * находится фишка
                                     * */
    /* Определяем метод для отрисовки фишки
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // CHIP_H
