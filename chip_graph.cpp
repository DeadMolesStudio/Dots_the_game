#include "chip_graph.h"

Chip_graph::Chip_graph() :
    QGraphicsItem()
{

}

Chip_graph::~Chip_graph()
{

}

QRectF Chip_graph::boundingRect() const
{
    return QRectF(-25,-25,50,50);   // Ограничиваем область, в которой лежит фишка

}

void Chip_graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawEllipse(-25, -25, 50, 50);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Chip_graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal1();
    this->moveBy(10, 10);
    // Вызываем родительскую функцию события нажатия кнопки мыши
    QGraphicsItem::mousePressEvent(event);
}

