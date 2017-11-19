#include "cell.h"

Cell::Cell(QWidget *parent) :
    QWidget(parent)
{
    pointer_chip = new Chip();
}

//Cell::Cell(Chip *chip, bool blocked) :
//    blocked(blocked), pointer_chip(chip)
//{

//}

Chip* Cell::get_chip()
{
    return pointer_chip;
}

void Cell::random_chip()
{
    delete pointer_chip;
    pointer_chip  = new Chip();
}

bool Cell::is_blocked()
{
    return blocked;
}

//QRectF Cell::boundingRect() const
//{
//    return QRectF(0,0,50,50);   // Ограничиваем область, в которой лежит фишка

//}

void Cell::paintEvent(QPaintEvent *event)
{
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawEllipse(0, 0, 50, 50);

}

void Cell::mousePressEvent(QMouseEvent *event)
{
    emit signal1();
    //this->moveBy(10, 10);
    // Вызываем родительскую функцию события нажатия кнопки мыши
    QWidget::mousePressEvent(event);
}

Cell::~Cell()
{
    delete pointer_chip;
}
