#include "cell.h"
#include <QApplication>
static const int CHIP_RADIUS = 25;

Cell::Cell(QWidget *parent) :
    QWidget(parent)
{
    pointer_chip = new Chip();
    in_combination = false;
    in_quadr = false;
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

bool Cell::is_in_quadr()
{
    return in_quadr;
}

void Cell::set_quadr_flag(bool value)
{
    in_quadr = value;
}

void Cell::paintEvent(QPaintEvent *event)
{

        Q_UNUSED(event);
        //qDebug("paintEvent");
        QPainter painter(this);
        update_chip_model(&painter);

        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::FlatCap));
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

Cell::~Cell()
{
    delete pointer_chip;
}

void Cell::activate()
{
    //qDebug("activate");
    in_combination = true;
    update();
}

void Cell::deactivate()
{
    //qDebug("deactivate");
    in_combination = false;
    update();
}

void Cell::activate_graphics(QPainter *painter)
{
    //qDebug("activate_graphics");
    painter->setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

}

void Cell::deactivate_graphics(QPainter *painter)
{
    //qDebug("deactivate_graphics");
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(1, 1, CHIP_RADIUS,CHIP_RADIUS);

}

void Cell::update_chip_model(QPainter *painter)
{
    //qDebug("update_chip_model");
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

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //qDebug("mousePressEvent");
    emit pressSignal();
    QWidget::mousePressEvent(event);
    //update();

}

void Cell::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //qDebug("mouseReleaseEvent");
    emit releaseSignal();
}

void Cell::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    //qDebug("enterEvent");
    emit enterSignal();
}


void Cell::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    //qDebug("leaveEvent");
    emit leaveSignal();
}

void Cell::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug("moveEvent");
    QPoint temp = mapToGlobal(event->pos());
    emit moveSignal(temp);
}

