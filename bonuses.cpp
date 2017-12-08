#include "bonuses.h"

Bonuses::Bonuses(QWidget *)
{
    createBonusesWindow();
    setAttribute(Qt::WA_QuitOnClose);
}

Bonuses::~Bonuses()
{
    grid->deleteLater();
    for (size_t i = 0; i < blocks.count(); i++)
    {
        blocks[i]->deleteLater();
    }
    blocks.clear();
    name->deleteLater();
}

void Bonuses::createBonusesWindow()
{
    name = new QTextEdit("Bonuses:", this);
    name->setContentsMargins(0,0,0,0);
    name->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    name->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    name->setAlignment(Qt::AlignRight);
    name->setAlignment(Qt::AlignCenter);
    name->setFrameStyle(0);
    name->setDisabled(true);
    name->setStyleSheet("QTextEdit {background-color: transparent}");
    name->setFixedHeight(30);


    current_quants = 0;
    for (size_t i = 0; i < 3; i++)
    {
        blocks.append(new QTextEdit(this));
        blocks.last()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        blocks.last()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        blocks.last()->setFrameStyle(0);
        blocks.last()->setDisabled(true);
        blocks.last()->setStyleSheet("QTextEdit {background-color: transparent; border-radius: 3px;}");
        //qDebug() << this->rect();
    }
}

void Bonuses::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Bonuses::addQuant(int color)
{
    //qDebug() << "addQuant";
    set_color(color);
    blocks[current_quants]->setFixedSize(this->rect().width()-10, 40);
    QPropertyAnimation *animation = new QPropertyAnimation(blocks[current_quants], "geometry");
    animation->setDuration(1000);

    animation->setStartValue(QRect(5,0,this->rect().width()-10, 40));
    animation->setEndValue(QRect(5, this->rect().bottom() - 45 * (current_quants + 1) + 1, this->rect().width()-10, 40));

    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();
    current_quants++;
    if (current_quants == 3)
    {
        //выбор бонуса
        //this->setStyleSheet("Bonuses{background-color: #abcdef;border-radius: 8px; border: 2px solid #dedede}");
        clear();
    }

}

void Bonuses::set_color(int color)
{
    switch(color)
    {
    case 0:
        //dark blue
        blocks[current_quants]->setStyleSheet("QTextEdit {background-color: #9370d8; border-radius: 3px;}");
        break;
    case 1:
        //yellow
        blocks[current_quants]->setStyleSheet("QTextEdit {background-color: #ffff99; border-radius: 3px;}");
        break;
    case 2:
        //purple
        blocks[current_quants]->setStyleSheet("QTextEdit {background-color: #ea8df7; border-radius: 3px;}");
        break;
    case 3:
        //red
        blocks[current_quants]->setStyleSheet("QTextEdit {background-color: #fc6c85; border-radius: 3px;}");
        break;
    case 4:
        //green
        blocks[current_quants]->setStyleSheet("QTextEdit {background-color: #ffc8a8; border-radius: 3px;}");
        break;
    default:
        QMessageBox::critical(this, "", "ошибка в выборе цвета");
    }
}

void Bonuses::clear()
{
    if (current_quants > 0)
    {
        QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
        for(size_t i = 0; i < current_quants; i++)
        {
            QPropertyAnimation *animation = new QPropertyAnimation(blocks[current_quants], "geometry");
            animation->setDuration(1000);

            animation->setStartValue(QRect(5, this->rect().bottom() - 45 + 1, this->rect().width()-10, 40));
            animation->setEndValue(QRect(pow(-1, i) * 300, this->rect().bottom() - 45 + 1, this->rect().width()-10, 40));

            animation->setEasingCurve(QEasingCurve::InCubic);
            group->addAnimation(animation);
            //animation->start();
        }
        group->start();
    }
    current_quants = 0;
    for (size_t i = 0; i < 3; i++)
    {
        //blocks[i]->setStyleSheet("QTextEdit {background-color: transparent; border-radius: 3px;}");
    }
}

