#include "level.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Level::Level(QWidget *, int max_moves, size_t rows, size_t cols) :
     score(0), max_moves(max_moves), cur_moves(0)
{
    winscore = this->max_moves * 5 * 3;
    field = new Field(this, rows, cols);
    selecter = new Selecter(this);
    selecter->raise();
    menu = new QPushButton("Menu\n");

    line_selecter = new Line_selecter(0, rows, QSize(field->width() - 20, field->height() - 15));

    reqs_done = 0;
    reqs.append(Requirement(Chip(1, 3), 3)); //красные треугольники

    reqset = new ReqSet(0, reqs);
    bonuses = new Bonuses();
    connect(field, &Field::quant_s, this, &Level::quants_SLOT);
    connect(this, &Level::quants_SIGNAL, bonuses, &Bonuses::addQuant);
    connect(this, &Level::update_reqs_info, reqset, &ReqSet::update_info_reqs_slot);
    connect(this, &Level::add_req_SIGNAL, reqset, &ReqSet::add_req);
    connect(field, &Field::plusScore, this, &Level::update_score_Slot);
    connect(field, &Field::check_reqs_for_cell, this, &Level::check_reqs_Slot);
    connect(field, &Field::not_quant, bonuses, &Bonuses::clear);
    connect(bonuses, &Bonuses::choose_bonuses, this, &Level::show_selecter);
    connect(selecter, &Selecter::selected, this, &Level::start_bonus);
    connect(this, &Level::choosed_line_SIGNAL,field, &Field::line_destroy_bonus);
    connect(this, &Level::random_bonus_SIGNAL,field, &Field::random_field_bonus);
    connect(this, &Level::color_bonus_SIGNAL,field, &Field::color_bonus);
    connect(line_selecter, &Line_selecter::choosed_line, this, &Level::hide_line_selecter);
    connect(field, &Field::add_extra_move, this, &Level::add_move);

    connect(this, &Level::enable_preset1, field, &Field::preset1);
    connect(this, &Level::enable_preset2, field, &Field::preset2);
    connect(this, &Level::enable_preset3, field, &Field::preset3);



    createLevelWindow();
}

void Level::choosed_level(uint number)
{
    qDebug() << "choosed level";
    switch (number) {
    case 0:

        break;
    case 1:
        level1();
        break;
    case 2:
        level2();
        break;
    case 3:
        level3();
        break;
    default:
        break;
    }
}

void Level::add_move()
{
    cur_moves--;
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
    menu->setStyleSheet("QPushButton{background-color: #efefff; border-radius: 8px; border: 2px solid #dedede; color: #7f7f7f}");
    connect(menu, &QPushButton::clicked, this, &Level::to_menu);
    grid = new QGridLayout();
    grid->setSpacing(0);
    info = new QGridLayout();
    info->addWidget(menu, 0, 0);
    info->setAlignment(menu, Qt::AlignLeft);
    menu->setFixedSize(field->width()/2 - 30, 40);

    //grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);
    text.append(new QTextEdit("Moves: " + QString::number(max_moves)));
    text.append(new QTextEdit("Score: " + QString::number(score)));
    text.append(new QTextEdit("WinScore: " + QString::number(winscore)));
    grid->addLayout(info,0,0,1,4);
//    grid->addWidget(selecter);

    for(size_t i = 0; i < text.count(); i++)
    {
        text[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text[i]->setFixedSize(field->width()/2 - 30, 40);
        text[i]->setFrameStyle(0);
        text[i]->setDisabled(true);
        text[i]->setStyleSheet("QTextEdit {background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");
        text[i]->setAlignment(Qt::AlignCenter);

        info->addWidget(text[i], 0, i + 1);
        info->setAlignment(text[i], Qt::AlignCenter);
    }
    info->setAlignment(text[0], Qt::AlignLeft);
    info->setAlignment(text[2], Qt::AlignRight);


    reqset->setFixedSize(field->width()/2 - 30, field->height() - 30);
    bonuses->resize(field->width()/2 - 30, field->height() - 30);
    bonuses->setFixedSize(field->width()/2 - 30, field->height() - 30);
    grid->addWidget(bonuses, 1, 0, 1, 1);
    grid->addWidget(field, 1, 1, 1, 2);
    grid->setAlignment(field, Qt::AlignHCenter);
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
        emit clear_me();
        emit to_menu_SIGNAL();
    }
    else
    {
        if(cur_moves >= max_moves)
        {
            QMessageBox::information(this, "ПОРАЖЕНИЕ", QString("Поражение! Ваши очки: ") + QString::number(score));
            emit clear_me();
            emit to_menu_SIGNAL();
        }
    }
}

void Level::check_reqs_Slot(Chip test)
{
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
            emit update_reqs_info(reqs);
            break;
        }
    }
}

void Level::quants_SLOT(int color)
{
    qDebug() << "quants_SLOT";
    emit quants_SIGNAL(color);
}

void Level::show_selecter()
{
    //selecter->show();
    this->setEnabled(0);
    selecter->setEnabled(1);
    //selecter->raise();
    emit show_selecter_SIGNAL(1);
}

void Level::hide_line_selecter(size_t number)
{
    grid->removeWidget(line_selecter);
    line_selecter->setVisible(0);
    emit choosed_line_SIGNAL(number);
}

void Level::add_req(int shape, int color, size_t demand)
{
    reqs.append(Requirement(Chip(shape, color), demand));
    emit add_req_SIGNAL(reqs.last());
}

void Level::level1()
{
    qDebug() << "level1";
    //this->retry();
    emit enable_preset1();
    //    reqs.append(Requirement(Chip(0, 0), 5)); //синие круги
    //    reqs.append(Requirement(Chip(1, 2), 4)); //сиреневые треугольники
    //    reqs.append(Requirement(Chip(0, 4), 4)); //оранжевые круги
    add_req(0, 0, 5);
}

void Level::level2()
{
    emit enable_preset2();
    add_req(0, 0, 5);
    add_req(1, 2, 4);
}

void Level::level3()
{
    emit enable_preset3();
    add_req(0, 0, 5);
    add_req(1, 2, 4);
    add_req(0, 4, 4);
}

void Level::to_menu()
{
    emit to_menu_SIGNAL();
}

void Level::start_bonus(int bonus)
{
    switch(bonus)
    {
    case 0:
        emit line_bonus_SIGNAL();
        grid->addWidget(line_selecter, 1, 1, 1, 2);
        line_selecter->setVisible(1);
        grid->setAlignment(line_selecter, Qt::AlignVCenter);
        grid->setAlignment(line_selecter, Qt::AlignHCenter);
        this->setEnabled(1);
        emit show_selecter_SIGNAL(0);
        break;
    case 1:
        emit random_bonus_SIGNAL();
        this->setEnabled(1);
        emit show_selecter_SIGNAL(0);
        break;
    case 2:
        emit color_bonus_SIGNAL();
        this->setEnabled(1);
        emit show_selecter_SIGNAL(0);
        break;
    default:
        qDebug() << "error in Level::start_bonus";
    }
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
    selecter->deleteLater();
}
