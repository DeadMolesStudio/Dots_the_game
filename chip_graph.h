#ifndef CHIP_H
#define CHIP_H

#include <QGraphicsItem>

#include <QWidget>

// Наследуемся от QGraphicsItem
class Chip_graph : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Chip_graph();
    ~Chip_graph();

    //void mouse
private:

        /* Определяем виртуальный метод,
                                     * который возвращает область, в которой
                                     * находится фишка
                                     * */
    /* Определяем метод для отрисовки фишки
     * */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



};


#endif // CHIP_H
