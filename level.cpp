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
    grid->setSpacing(SPACE);
    grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);
    //QPushButton *exit = new QPushButton();

    score_text = new QTextEdit(QString::number(score));
    score_text->setFixedSize(field->width(), 40);
    score_text->setFrameStyle(0);
    score_text->setDisabled(true);
    score_text->setStyleSheet("QTextEdit {background-color: #efefff; border-radius: 8px; border: 2px solid #dedede}");


    grid->addWidget(score_text, 0, 0);
   // grid->setMenuBar(score_text);
    grid->addWidget(field, 1, 0);
    this->setLayout(grid);
    //this->setFixedSize(field->width(), field->height() + score_text->height());
    this->setFixedSize(this->sizeHint());
}

void Level::update_score_Slot(unsigned int add_score)
{
    qDebug("update_score_Slot");
    score += add_score;
}

Level::~Level()
{
    delete grid;
    delete field;
}
