#include "cell.h"

static const int CHIP_RADIUS = 25;

Cell::Cell(QWidget *parent) :
    QWidget(parent)
{
    pointer_chip = new Chip();
    in_combination = false;
    this->setFixedSize(CHIP_RADIUS + 2,CHIP_RADIUS + 2);
}


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

bool Cell::is_in_combination()
{
    return in_combination;
}

void Cell::paintEvent(QPaintEvent *event)
{

        Q_UNUSED(event);
        qDebug("paintEvent");
        QPainter painter(this);
        update_chip_model(&painter);

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

        if (in_combination)
        {
            activate_graphics(&painter);
        }
        else
        {
            deactivate_graphics(&painter);
        }
}


void Cell::mousePressEvent(QMouseEvent *event)
{
    emit signal1();
    qDebug("mousePressEvent");
    QWidget::mousePressEvent(event);
    update();

}

Cell::~Cell()
{
    delete pointer_chip;
}

void Cell::activate()
{
    qDebug("activate");
    in_combination = true;
    update();
}

void Cell::deactivate()
{
    qDebug("deactivate");
    in_combination = false;
    update();
}

void Cell::activate_graphics(QPainter *painter)
{
    qDebug("activate_graphics");
    painter->setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

}

void Cell::deactivate_graphics(QPainter *painter)
{
    qDebug("deactivate_graphics");
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

}

void Cell::update_chip_model(QPainter *painter)
{
    qDebug("update_chip_model");
    switch(pointer_chip->color)
    {
    case 0:
        //dark blue
        painter->setBrush(QBrush(QColor(QRgb(Chip_colors::Dark_blue)), Qt::SolidPattern));
        break;
    case 1:
        //yellow
        painter->setBrush(QBrush(QColor(QRgb(Chip_colors::Yellow)), Qt::SolidPattern));
        break;
    case 2:
        //purple
        painter->setBrush(QBrush(QColor(QRgb(Chip_colors::Purple)), Qt::SolidPattern));
        break;
    case 3:
        //red
        painter->setBrush(QBrush(QColor(QRgb(Chip_colors::Red)), Qt::SolidPattern));
        break;
    case 4:
        //green
        painter->setBrush(QBrush(QColor(QRgb(Chip_colors::Green)), Qt::SolidPattern));
        break;
    default:
        painter->setBrush(QBrush(QColor(QRgb(0x000000)), Qt::SolidPattern));
        QMessageBox::critical(this, "", "ошибка в выбооре цвета");
    }
}

//void Cell::enterEvent(QEvent *event)
//{
//    Q_UNUSED(event);
//    //QPalette Pal(palette());
////    // устанавливаем цвет фона
////    Pal.setColor(QPalette::Background, QColor(QRgb(0x000000)));
////    this->setAutoFillBackground(true);
////    this->setPalette();
//    QPainter painter;
//    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));
//    painter.drawEllipse(CHIP_RADIUS/2 - 2,CHIP_RADIUS/2 - 2,4,4);
//    qDebug("enter");
//}

//void Cell::leaveEvent(QEvent *event)
//{
//    Q_UNUSED(event);
//    QPainter painter;
//    painter.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
//    painter.drawEllipse(CHIP_RADIUS/2 - 2,CHIP_RADIUS/2 - 2,4,4);
////    QPalette Pal(palette());
////    // устанавливаем цвет фона
////    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
////    this->setAutoFillBackground(true);
////    this->setPalette(Pal);
//    qDebug("leave");
//}

//void Cell::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//        QPalette Pal(palette());
//        // устанавливаем цвет фона
//        Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
//        this->setAutoFillBackground(true);
//        this->setPalette(Pal);
//        deactivate();
//}
