#include "cell.h"

static const int CHIP_RADIUS = 25;

Cell::Cell(QWidget *parent) :
    QWidget(parent)
{
    pointer_chip = new Chip();
    in_combination = 0;
    this->setFixedSize(CHIP_RADIUS +2,CHIP_RADIUS +2);
    // устанавливаем цвет фона
//    QPalette Pal(palette());
//    Pal.setColor(QPalette::Background, Qt::green);
//    this->setAutoFillBackground(true);
//    this->setPalette(Pal);
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
    in_combination = 0;
}

bool Cell::is_blocked()
{
    return blocked;
}

//QRectF Cell::boundingRect() const
//{
//    return QRectF(0,0,30,30);   // Ограничиваем область, в которой лежит фишка

//}

void Cell::paintEvent(QPaintEvent *event)
{
        Q_UNUSED(event);
        QPainter painter(this);
        switch(pointer_chip->color)
        {
        case 0:
            painter.setBrush(QBrush(QColor(157,129,186,255), Qt::SolidPattern));
            break;
        case 1:
            painter.setBrush(QBrush(QColor(255,255,82,255), Qt::SolidPattern));
            break;
        case 2:
            painter.setBrush(QBrush(QColor(0,255,127,255), Qt::SolidPattern));
            break;
        case 3:
            painter.setBrush(QBrush(QColor(0,65,106,255), Qt::SolidPattern));
            break;
        case 4:
            painter.setBrush(QBrush(QColor(197,29,52,255), Qt::SolidPattern));
            break;
        default:
            QMessageBox::critical(this, QString("ЭТО не работает"), "ошибка в выбооре цвета");
            break;
        }


        switch(in_combination){
        case 0:
            painter.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
            painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);
            in_combination = 1;
            break;

        case 1:
            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
            painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);
            in_combination = 0;
            break;
        }
//        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
//        painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);
}

void Cell::mousePressEvent(QMouseEvent *event)
{

    paintEvent(0);
//    QString temp("Color: " + QString::number(this->get_chip()->color) + "\nShape: " + QString::number(this->get_chip()->shape));
//    QMessageBox msgBox;
//    msgBox.setText("Информация о фишке:");
//    msgBox.setInformativeText(temp);
//    msgBox.exec();



    QWidget::mousePressEvent(event);
    emit signal1();
}

Cell::~Cell()
{
    delete pointer_chip;
}
