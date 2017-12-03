#include "level.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Level::Level(QWidget *, int max_moves, size_t rows, size_t cols) :
     score(0), max_moves(max_moves), cur_moves(0)
{
    field = new Field(this, rows, cols);
    reqs.append(Requirement(Chip(1, 3), 6)); //красные треугольники
    reqs.append(Requirement(Chip(0, 0), 15)); //синие круги
    reqs.append(Requirement(Chip(1, 2), 4)); //красные треугольники
    reqs.append(Requirement(Chip(0, 4), 4)); //синие круги
    reqset = new ReqSet(0, reqs);
    connect(this, &Level::update_reqs_info, reqset, &ReqSet::update_info_reqs_slot);
    connect(field, &Field::plusScore, this, &Level::update_score_Slot);
    connect(field, &Field::check_reqs_for_cell, this, &Level::check_reqs_Slot);
    createLevelWindow();
}

void Level::createLevelWindow()
{
    setAttribute(Qt::WA_QuitOnClose);
    this->setWindowTitle(QString("Dots"));
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    grid = new QGridLayout();
    grid->setSpacing(0);
    //grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);
    text.append(new QTextEdit("Moves: " + QString::number(max_moves)));
    text.append(new QTextEdit("Score: " + QString::number(score)));
    text.append(new QTextEdit("WinScore:\n" + QString::number(max_moves * 5 * 3)));

    for(size_t i = 0; i < text.count(); i++)
    {
        text[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setFixedSize(field->width()/2 - 30, 40);
        text[i]->setFrameStyle(0);
        text[i]->setDisabled(true);
        text[i]->setStyleSheet("QTextEdit {background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");
        text[i]->setAlignment(Qt::AlignCenter);
    }

    grid->addWidget(text[0], 0, 0);
    grid->addWidget(text[1], 0, 1);
    grid->addWidget(text[2], 0, 2);
    grid->setAlignment(text[0], Qt::AlignHCenter);
    grid->setAlignment(text[1], Qt::AlignHCenter);
    grid->setAlignment(text[2], Qt::AlignHCenter);
    grid->addWidget(field, 1, 0, 1, 2);
    grid->addWidget(reqset,1, 2);
    this->setLayout(grid);
    //this->setFixedSize(field->width(), field->height() + score_text->height());
    this->setFixedSize(this->sizeHint());
}

void Level::update_score_Slot(unsigned int add_score)
{
    //qDebug() << "update_score_Slot:" << add_score;
    score += add_score;
    cur_moves++;
    text[1]->setText("Score: " + QString::number(score));
    text[0]->setText("Moves: " + QString::number(max_moves - cur_moves));
    text[1]->setAlignment(Qt::AlignCenter);
    text[0]->setAlignment(Qt::AlignCenter);
    if (score >= max_moves * 5 * 3)
    {
        unsigned int bonus = (max_moves - cur_moves) * 5 * 3;
        QMessageBox::information(this, "ПОБЕДА", QString("Победа! Ваши очки: ") + QString::number(score) +
                                 QString("\nБонус за оставшиеся ходы: ") + QString::number(bonus) +
                                 QString("\nВсего: ") + QString::number(score+bonus));
        QCoreApplication::exit();
    }
    else
    {
        if(cur_moves >= max_moves)
        {
            QMessageBox::information(this, "ПОРАЖЕНИЕ", QString("Поражение! Ваши очки: ") + QString::number(score));
            QCoreApplication::exit();
        }
    }
}

void Level::check_reqs_Slot(Chip test)
{
    bool edited = 0;
    for (size_t i = 0; i < reqs.count(); i++)
    {
        if (reqs[i].check(test))
        {
            edited = 1;
            break;
        }
    }
    if (edited)
    {
        emit update_reqs_info(reqs);
    }
}

Level::~Level()
{
    for (size_t i = 0; i < text.count(); i++)
    {
        text[i]->deleteLater();
    }
    grid->deleteLater();
    field->deleteLater();
    reqset->deleteLater();

}
