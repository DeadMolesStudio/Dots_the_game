#include "level.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Level::Level(QWidget *, int max_moves, size_t rows, size_t cols) :
     score(0), max_moves(max_moves), cur_moves(0)
{
    field = new Field(this, rows, cols);
    connect(field, &Field::plusScore, this, &Level::update_score_Slot);
    createLevelWindow();
}

void Level::createLevelWindow()
{
    this->setWindowTitle(QString("Dots"));
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    grid = new QGridLayout();
    //grid->setSpacing(SPACE);
    grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);
    //QPushButton *exit = new QPushButton();

    text.append(new QTextEdit("Moves: " + QString::number(max_moves)));
    text.append(new QTextEdit("Score: " + QString::number(score)));
    for(size_t i = 0; i < text.count(); i++)
    {
        text[i]->setFixedSize(field->width()/2 - 30, 40);
        text[i]->setFrameStyle(0);
        text[i]->setDisabled(true);
        text[i]->setStyleSheet("QTextEdit {background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");
        text[i]->setAlignment(Qt::AlignCenter);
    }

    grid->addWidget(text[0], 0, 0);
    grid->addWidget(text[1], 0, 1);
    grid->setAlignment(text[0], Qt::AlignHCenter);
    grid->setAlignment(text[1], Qt::AlignHCenter);
   // grid->setMenuBar(score_text);
    grid->addWidget(field, 1, 0, 1, 2);
    this->setLayout(grid);
    //this->setFixedSize(field->width(), field->height() + score_text->height());
    this->setFixedSize(this->sizeHint());
}

void Level::update_score_Slot(unsigned int add_score)
{
    qDebug() << "update_score_Slot:" << add_score;
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
                                 QString("\nБонус за ходы: ") + QString::number(bonus) +
                                 QString("\nВсего: ") + QString::number(score+bonus));
        this->close();
    }
    else
    {
        if(cur_moves >= max_moves)
        {
            QMessageBox::information(this, "ПОРАЖЕНИЕ", QString("Поражение! Ваши очки: ") + QString::number(score));
            this->close();
        }
    }
}

Level::~Level()
{
    delete grid;
    delete field;
}
