#include "selecter.h"


Selecter::Selecter(QWidget *)
{
    createSelecterWindow();
    setAttribute(Qt::WA_QuitOnClose);
}

Selecter::~Selecter()
{
    buttons.clear();
}

void Selecter::createSelecterWindow()
{
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));//first
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setWindowTitle("Dots");
    grid = new QGridLayout();

    for (size_t i = 0; i < 3; i++)
    {
        labels.append(new QLabel);
    }
    labels[0]->setMovie(new QMovie(":/images/line.gif"));
    labels[1]->setMovie(new QMovie(":/images/random.gif"));
    labels[2]->setMovie(new QMovie(":/images/color.gif"));

    labels[0]->movie()->start();
    labels[1]->movie()->start();
    labels[2]->movie()->start();

    buttons.append(new QPushButton(""));
    buttons.append(new QPushButton(""));
    buttons.append(new QPushButton(""));
    connect(buttons[0], &QPushButton::clicked, this, &Selecter::line_clicked);
    connect(buttons[1], &QPushButton::clicked, this, &Selecter::random_clicked);
    connect(buttons[2], &QPushButton::clicked, this, &Selecter::color_clicked);

    for (size_t i = 0; i < buttons.count(); i++)
    {
        buttons[i]->setFixedSize(100, 200);
        buttons[i]->setStyleSheet("QPushButton{background-color: rgba(239, 239, 255, 100); border-radius: 8px; border: 2px solid #dedede;}");
        grid->addWidget(labels[i], 0, i);
        grid->addWidget(buttons[i], 0, i);
        grid->setAlignment(labels[i], Qt::AlignHCenter);
    }

    this->setLayout(grid);
}

void Selecter::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Selecter::line_clicked()
{
    emit selected(0);
    this->setEnabled(0);
//    this->setVisible(0);
}

void Selecter::random_clicked()
{
    emit selected(1);
    this->setEnabled(0);
//    this->setVisible(0);
}

void Selecter::color_clicked()
{
    emit selected(2);
    this->setEnabled(0);
//    this->setVisible(0);
}


