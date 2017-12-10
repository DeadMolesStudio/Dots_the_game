#include "level_selecter.h"

Level_selecter::Level_selecter(QWidget *, size_t count)
    : count(count)
{
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));//first
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    back = new QPushButton("Menu");
    back->setStyleSheet("QPushButton{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede;}");
    back->setFixedSize(100, 50);

    connect(back, &QPushButton::clicked, this, &Level_selecter::to_menu);
    grid = new QGridLayout();
    QImage *image = new QImage();
    //grid->addWidget(image, 0, 1);
    for (size_t i = 0; i < count; i++)
    {
        buttons.append(new QPushButton(QString::number(i), this));
        connect(buttons.last(), &QPushButton::clicked, this, &Level_selecter::pressed);
        buttons[i]->setFixedSize(80, 80);
        buttons[i]->setStyleSheet("QPushButton{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede;}");
        grid->addWidget(buttons[i], 1, i);
        grid->setAlignment(buttons[i], Qt::AlignHCenter);
    }
    grid->addWidget(back, 2, 0, 1, count);
    grid->setAlignment(back, Qt::AlignHCenter);
    this->setFixedSize(400, 200);
    this->setLayout(grid);
}

void Level_selecter::to_menu()
{
    emit to_menu_SIGNAL();
}

void Level_selecter::pressed()
{
    qDebug() << "pressed in LEvel_selecter";

    emit selected_level(qobject_cast<QPushButton*>(sender())->text().toUInt());
    //emit play_SIGNAL();
}
