#include "menu.h"

Menu::Menu(QWidget *)
{
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));//first
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setWindowTitle("Dots");
    layout = new QGridLayout();

    logo = new QLabel();
    QPixmap temp(":/images/logo.png");
    temp.load(":/images/logo.png");
    logo->setPixmap(temp);
    logo->setScaledContents(true);
    logo->setFixedSize(150, 50);

    layout->addWidget(logo, 0, 0);
    buttons.append(new QPushButton("Play"));
    buttons.append(new QPushButton("Select level"));
    buttons.append(new QPushButton("Help"));
    buttons.append(new QPushButton("Quit"));
    for (size_t i = 0; i < buttons.count(); i++)
    {
        buttons[i]->setFixedSize(150, 50);
        buttons[i]->setStyleSheet("QPushButton{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede;}");
        layout->addWidget(buttons[i], i + 1, 0);
        layout->setAlignment(buttons[i], Qt::AlignHCenter);
    }
    qDebug() << "??";
    connect(buttons[0], &QPushButton::clicked, this, &Menu::play_SLOT);
    connect(buttons[1], &QPushButton::clicked, this, &Menu::choose_level_SLOT);
    connect(buttons[2], &QPushButton::clicked, this, &Menu::help_SLOT);
    connect(buttons.last(), &QPushButton::clicked, this, &Menu::quit_SLOT);
    this->setFixedSize(400, 200);
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

void Menu::help_SLOT()
{
    emit help_SIGNAL();
}
