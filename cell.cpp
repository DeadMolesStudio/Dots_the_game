#include "cell.h"
////TODO:избавиться от макросов
//#define YELLOW 255,244,79,255
//#define GREEN 0,106,78,255
//#define DARK_BLUE 60,99,240,255
//#define RED 255,42,77,255
//#define PURPLE 153,102,204,255
#include <QColor>
#include <QRgb>

enum class Chip_colors {
    Yellow = 0xffff99,
    Green = 0xffc8a8,
    Dark_blue = 0x9370d8,
    Red = 0xfc6c85,
    Purple = 0xea8df7
};

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

void Cell::paintEvent(QPaintEvent *event)
{

        Q_UNUSED(event);
        QPainter painter(this);
        update_chip_model(&painter);

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

//        switch (in_combination) {
//        case 0:
//            activate_graphics(&painter);
//            break;
//        case 1:
//            deactivate_graphics(&painter);
//            break;
//        }

        if (in_combination)
        {
            activate_graphics(&painter);
        }
        else
        {
            deactivate_graphics(&painter);
        }
}

/*
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

            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
            painter.drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

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
}
*/

void Cell::mousePressEvent(QMouseEvent *event)
{


//    QString temp("Color: " + QString::number(this->get_chip()->color) + "\nShape: " + QString::number(this->get_chip()->shape));
//    QMessageBox msgBox;
//    msgBox.setText("Информация о фишке:");
//    msgBox.setInformativeText(temp);
//    msgBox.exec();

    QWidget::mousePressEvent(event);
    update();
    emit signal1();
}

Cell::~Cell()
{
    delete pointer_chip;
}

void Cell::activate()
{
    in_combination = 1;
    update();
}

void Cell::deactivate()
{
    in_combination = 0;
    update();
}

void Cell::activate_graphics(QPainter *painter)
{
    painter->setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);
    in_combination = 1;
}

void Cell::deactivate_graphics(QPainter *painter)
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);
    in_combination = 0;
}

void Cell::update_chip_model(QPainter *painter)
{
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
        break;
    }
}
