#include "reqset.h"

static const int CHIP_RADIUS = 25;

ReqSet::ReqSet(QWidget*, QVector<Requirement> reqs)
{
    for (size_t i = 0; i < reqs.count(); i++)
    {
        //elems.append(req_element(reqs[i].get_sample(), reqs[i].left()));
        numbers.append(new QTextEdit(QString::number(reqs[i].left())));
        icons.append(new Cell(0, reqs[i].get_sample(), 0));
    }
    setAttribute(Qt::WA_QuitOnClose);
    create_req_Window();

}

ReqSet::~ReqSet()
{
    grid->deleteLater();
    name->deleteLater();
    for (size_t i = 0; i < icons.count(); i++)
    {
        //elems[i].cell->deleteLater();
        icons[i]->deleteLater();
        numbers[i]->deleteLater();
    }
    icons.clear();
    numbers.clear();
}

void ReqSet::create_req_Window()
{
    //this->setFixedSize(100, 100);    // Фиксируем размеры виджета(окна)
//    QPalette Pal(palette());
//    // устанавливаем цвет фона
//    Pal.setColor(QPalette::Background, QColor(QRgb(0xffeedd)));
//    this->setAutoFillBackground(true);
//    this->setPalette(Pal);
    //this->setStyleSheet("this {color: #000; background-color: transparent; border: 2px solid #000}");
    grid = new QGridLayout();


    name = new QTextEdit("Require");
    name->setContentsMargins(0,0,0,0);

    name->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    name->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    name->setAlignment(Qt::AlignRight);
    name->setAlignment(Qt::AlignCenter);
    name->setFrameStyle(0);
    name->setDisabled(true);
    name->setStyleSheet("QTextEdit {background-color: transparent}");
    name->setFixedHeight(30);
    //name->setAlignment(Qt::AlignTop);
    //grid->addWidget(name, 0, 0, 1, 2);
    grid->setMenuBar(name);
    //grid->itemAtPosition(0,0)->setGeometry(QRect(1,1,80,30));

    for (size_t i = 0; i < icons.count(); i++)
    {
        numbers[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        numbers[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        numbers[i]->setFixedSize(CHIP_RADIUS + 2, CHIP_RADIUS + 2);
        numbers[i]->setAlignment(Qt::AlignRight);
        numbers[i]->setAlignment(Qt::AlignCenter);
        numbers[i]->setFrameStyle(0);
        numbers[i]->setDisabled(true);
        grid->setRowStretch(i + 1, 0);
        numbers[i]->setStyleSheet("QTextEdit {background-color: transparent;}");
        //numbers[i]->setPalette(QBrush(Qt::NoBrush));
        //numbers[i]->setAttribute( Qt::WA_TranslucentBackground, true );

        grid->addWidget(numbers[i], i, 0);
        grid->addWidget(icons[i], i, 1);

    }

    this->setLayout(grid);
}

void ReqSet::update_info_reqs_slot(QVector<Requirement> reqs)
{
    for (size_t i = 0; i < reqs.count(); i++)
    {
        //elems.append(req_element(reqs[i].get_sample(), reqs[i].left()));
        numbers[i]->setText(QString::number(reqs[i].left()));
        numbers[i]->setAlignment(Qt::AlignRight);
        numbers[i]->setAlignment(Qt::AlignCenter);
    }

}

void ReqSet::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}



