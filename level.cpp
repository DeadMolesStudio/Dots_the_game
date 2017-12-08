#include "level.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Level::Level(QWidget *, int max_moves, size_t rows, size_t cols) :
     score(0), max_moves(max_moves), cur_moves(0)
{
    winscore = this->max_moves * 5 * 3;
    field = new Field(this, rows, cols);
    reqs_done = 0;
    reqs.append(Requirement(Chip(1, 3), 3)); //красные треугольники
    reqs.append(Requirement(Chip(0, 0), 5)); //синие круги
    reqs.append(Requirement(Chip(1, 2), 4)); //красные треугольники
    reqs.append(Requirement(Chip(0, 4), 4)); //синие круги
    reqset = new ReqSet(0, reqs);
    bonuses = new Bonuses();
    connect(field, &Field::quant_s, this, &Level::quants_SLOT);
    connect(this, &Level::quants_SIGNAL, bonuses, &Bonuses::addQuant);
    connect(this, &Level::update_reqs_info, reqset, &ReqSet::update_info_reqs_slot);
    connect(field, &Field::plusScore, this, &Level::update_score_Slot);
    connect(field, &Field::check_reqs_for_cell, this, &Level::check_reqs_Slot);
    connect(field, &Field::not_quant, bonuses, &Bonuses::clear);

    createLevelWindow();
}

void Level::createLevelWindow()
{
    setAttribute(Qt::WA_QuitOnClose);
    this->setWindowTitle(QString("Dots"));
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));//first

    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    bonuses->setStyleSheet("Bonuses{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");
    reqset->setStyleSheet("ReqSet{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");

    grid = new QGridLayout();
    grid->setSpacing(0);
    info = new QGridLayout();

    //grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);
    text.append(new QTextEdit("Moves: " + QString::number(max_moves)));
    text.append(new QTextEdit("Score: " + QString::number(score)));
    text.append(new QTextEdit("WinScore: " + QString::number(winscore)));
    grid->addLayout(info,0,0,1,4);

    for(size_t i = 0; i < text.count(); i++)
    {
        text[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setFixedSize(field->width()/2 - 30, 40);
        text[i]->setFrameStyle(0);
        text[i]->setDisabled(true);
        text[i]->setStyleSheet("QTextEdit {background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");
        text[i]->setAlignment(Qt::AlignCenter);

        info->addWidget(text[i], 0, i);
        info->setAlignment(text[i], Qt::AlignCenter);
    }
    info->setAlignment(text[0], Qt::AlignLeft);
    info->setAlignment(text[2], Qt::AlignRight);

    reqset->setFixedSize(field->width()/2 - 30, field->height() - 30);
    bonuses->resize(field->width()/2 - 30, field->height() - 30);
    bonuses->setFixedSize(field->width()/2 - 30, field->height() - 30);
    grid->addWidget(bonuses, 1, 0, 1, 1);
    grid->addWidget(field, 1, 1, 1, 2);
    grid->addWidget(reqset,1, 3);
    //qDebug() << field->rect();
    this->setLayout(grid);
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
    if (score >= winscore && reqs_done)
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
    bool didnt_done = 0;
    for (size_t i = 0; i < reqs.count(); i++)
    {
        if (!reqs[i].is_done())
        {
            didnt_done = 1;
            break;
        }
    }

    if (didnt_done == 0)
    {
        reqs_done = 1;
    }

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

void Level::quants_SLOT(int color)
{
    qDebug() << "quants_SLOT";
    emit quants_SIGNAL(color);
}

Level::~Level()
{
    for (size_t i = 0; i < text.count(); i++)
    {
        text[i]->deleteLater();
    }
    grid->deleteLater();
    info->deleteLater();
    field->deleteLater();
    reqset->deleteLater();
}
