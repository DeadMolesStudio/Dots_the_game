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
    return QRectF(-25,-25,50,50);   // Ограничиваем область, в которой лежит f
}

void Chip_graph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter->drawEllipse(-25, -25, 50, 50);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Chip_graph::click()
{
    this->setPos(-250,-250);
}
