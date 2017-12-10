#include "menu.h"

Menu::Menu(QWidget *)
{
    layout = new QGridLayout();
    buttons.append(new QPushButton("Play"));
    buttons.append(new QPushButton("Select level"));
    buttons.append(new QPushButton("Quit"));

    for (size_t i = 0; i < buttons.count(); i++)
    {
        buttons[i]->setFixedSize(150, 50);
        layout->addWidget(buttons[i], i, 0);
    }
    qDebug() << "??";
    connect(buttons[0], &QPushButton::clicked, this, &Menu::play_SLOT);
    connect(buttons[1], &QPushButton::clicked, this, &Menu::choose_level_SLOT);
    connect(buttons.last(), &QPushButton::clicked, this, &Menu::quit_SLOT);
    this->setFixedSize(400, 300);
    this->setLayout(layout);
}


void Menu::quit_SLOT()
{
    emit quit_SIGNAL();
}

void Menu::choose_level_SLOT()
{
    emit choose_level_SIGNAL();
}

void Menu::play_SLOT()
{
    emit play_SIGNAL();
}
