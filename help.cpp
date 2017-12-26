#include "help.h"

Help::Help(QWidget *)
{
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));//first
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    back = new QPushButton("Menu");
    back->setStyleSheet("QPushButton{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede;}");
    back->setFixedSize(100, 50);

    connect(back, &QPushButton::clicked, this, &Help::to_menu);
    grid = new QGridLayout();
    logo = new QLabel();
    QPixmap temp(":/images/logo.png");
    temp.load(":/images/logo.png");
    logo->setPixmap(temp);
    logo->setScaledContents(true);
    logo->setFixedSize(150, 50);

    grid->addWidget(logo, 0, 0, 1, 3);
    grid->setAlignment(logo, Qt::AlignHCenter);

    QString text1 = "   Мы рады приветствовать тебя в нашей увлекательной игре Dots!\n";
    text1 += "Правила нашей игры действительно просты. Соединяй соседние точки, набирай очки, выполняй задания!\n";
    text1 += "Ты можешь объединять в одну длинную линию любой формы сколько угодно фишек одного цвета.\n";
    text1 += "Можно объединять треугольники с кружочками, если они одного цвета! \nКруги стоят 5 очков, а тругольники целых 10!!\n";
    text1 += "В этом тебе помогут бонусы! В твоем распоряжении квадры! Собери четыре фишки одного цвета рядом\n";
    text1 += "Зацикли квадратик, наведя снова на первую фишку... ВУАЛЯ! Уничтожились все фишки этого цвета на поле!!!";
    QString text3 = "Еще у тебя есть возможность получить один из трех супер-бонусов\n";
    text3 += "Собери три раза по пять или более фишек и выбери бонус!\n";
    text3 +="Первый собирает все фишки с выбранной линиии, второй регенерирует новое поле\n";
    text3 += "третий - собирает все фишки одного случайно выбранного цвета!";

    text.append(new QPlainTextEdit(text1));
    text.append(new QPlainTextEdit(text3));

    grid->addWidget(text[0], 1, 0, 1, 3);
    grid->addWidget(text[1], 3, 0, 1, 3);
    for (size_t i = 0; i < 3; i++)
    {
        labels.append(new QLabel);
        grid->addWidget(labels[i], 4, i);
        grid->setAlignment(labels[i], Qt::AlignHCenter);
    }

    for (size_t i = 0; i < text.count(); i++)
    {
        text[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setFrameStyle(0);
        text[i]->setDisabled(true);
        text[i]->setStyleSheet("QPlainTextEdit {background-color: transparent;}");
    }

    labels[0]->setMovie(new QMovie(":/images/line.gif"));
    labels[1]->setMovie(new QMovie(":/images/random.gif"));
    labels[2]->setMovie(new QMovie(":/images/color.gif"));

    labels[0]->movie()->start();
    labels[1]->movie()->start();
    labels[2]->movie()->start();
    QGridLayout *temp_layout = new QGridLayout();
    temp_layout->setContentsMargins(50, 0, 50, 0);
    for (size_t i = 0; i < 2; i++)
    {
        labels.append(new QLabel);
        temp_layout->addWidget(labels[i+3], 0, i);
//        temp_layout->setAlignment(labels[i+3], Qt::AlignHCenter);
//        temp_layout->setAlignment(labels[i+3], Qt::AlignTop);
//        grid->addWidget(labels[i+3], 2, i);
//        grid->setAlignment(labels[i+3], Qt::AlignRight);
//        grid->setAlignment(labels[i+3], Qt::AlignTop);
//        labels[i+3]->setFixedHeight(100);
//        labels[i+3]->setScaledContents(true);

    }
    grid->addLayout(temp_layout, 2, 0, 1, 3);
    //grid->setAlignment()
    labels[3]->setMovie(new QMovie(":/images/pole.gif"));
    labels[4]->setMovie(new QMovie(":/images/reqs.gif"));

    labels[3]->movie()->start();
    labels[4]->movie()->start();

    grid->addWidget(back, 5, 0, 1, 3);
    grid->setAlignment(back, Qt::AlignHCenter);
    this->setFixedSize(400, 200);
    this->setLayout(grid);
}

void Help::to_menu_SLOT()
{
    emit to_menu();
}
