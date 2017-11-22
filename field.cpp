#include "field.h"
#include "ui_field.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Field::Field(QWidget *,size_t rows, size_t cols) :
    rows(rows), cols(cols)
{
    createWindow();
}

Cell* Field::get_cell(size_t row, size_t col)
{
    return cell_matrix[row][col];
}

void Field::random_field()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (!cell_matrix[i][j]->is_blocked())
            {
                cell_matrix[i][j]->random_chip();
            }
        }
    }
}

void Field::check_field()//проверяет наличие комбинаций на поле(шахматный порядок(чекнуть в случае с вырезами у краев))
{
    while (true)
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = (i % 2); j < cols-2; j+=2)
            {
               if (check_cell(i, j)) return;
            }
        }
        random_field();
    }
}

bool Field::check_cell(size_t row, size_t col)
{
    if (cell_matrix[row][col]->is_blocked()) return 0;
    //up
    if(row > 1)
    {
        if (cell_matrix[row-1][col]->get_chip()->color == cell_matrix[row][col]->get_chip()->color) return 1;
    }
    //down
    if(row < rows - 1)
    {
        if (cell_matrix[row+1][col]->get_chip()->color == cell_matrix[row][col]->get_chip()->color) return 1;
    }
    //left
    if(col > 1)
    {
        if (cell_matrix[row][col-1]->get_chip()->color == cell_matrix[row][col]->get_chip()->color) return 1;
    }
    //right
    if(col < cols - 1)
    {
        if (cell_matrix[row][col+1]->get_chip()->color == cell_matrix[row][col]->get_chip()->color) return 1;
    }
    return 0;
}

Field::~Field()
{
    for (size_t i = 0; i < rows; i++)
    {
        delete [] cell_matrix[i];
    }
    delete [] cell_matrix;
    combination.clear();
    delete grid;
}

void Field::slotFromChip()
{
    if(combination.isEmpty())
    {
    //если первая фишка в комбинации
        {
        QMessageBox::information(this, QString("Combination"),
                                 QString("First added to combination:\n"
                                         "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                         )
                                 );

        }
        combination.append( qobject_cast<Cell*>(sender()) );
    }
    //если это не первая фишка
    else
    {
        if (qobject_cast<Cell*>(sender())->get_chip()->color == combination.last()->get_chip()->color)
                //если цвет совпадает
        {
            if ( adjacency_check(qobject_cast<Cell*>(sender())) )
            {
                if (qobject_cast<Cell*>(sender()) != combination.last())
                {
                   if ( !qobject_cast<Cell*>(sender())->is_in_combination() )
                   {
                       combination.append( qobject_cast<Cell*>(sender()) );
                       {
                           QMessageBox::information(this, QString("Combination"),
                                                    QString("Added to combination:\n"
                                                            "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color) +
                                                            "\nchips in combination:" + QString::number(combination.count())
                                                            )
                                                         );
                            }
                   }
                   else
                   {
                       {
                           QMessageBox::information(this, QString("Combination"),
                                                     QString("Chip is already in combination:\n"
                                                             "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color))
                                                     );
                       }
                       qobject_cast<Cell*>(sender())->activate();
                   }
                }
                else
                {
                    if (combination.count() == 1)
                    {
                        {
                            QMessageBox::critical(this, QString("Combination"),
                                                  QString("Combination cancelled because just one item!:\n"
                                                          "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                                          )
                                                     );
                        }
                        combination.clear();
                    }
                    else
                    {
                        {
                            QMessageBox::critical(this, QString("Combination"),
                                                  QString("Combination complete!:\n"
                                                          "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                                          )
                                                     );
                        }
                        complete_combination();
                    }
                }
            }
            else
            {


                {
                QMessageBox::warning(this, QString("Combination"),
                                         QString("Фишка не соседняя!!:\n"
                                                 "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                                 )
                                         );
                }
               qobject_cast<Cell*>(sender())->deactivate();
            }
        }
        else //цвет не совпадает
        {
            if ( adjacency_check(qobject_cast<Cell*>(sender())) )
            {

                {
                QMessageBox::warning(this, QString("Combination"),
                                         QString("Фишка не подходит по цвету!:\n"
                                                 "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                                 )
                                         );
                }
            qobject_cast<Cell*>(sender())->deactivate();
            }
            else
            {

                {
                QMessageBox::warning(this, QString("Combination"),
                                         QString("Фишка не соседняя!!:\n"
                                                 "color:" + QString::number( qobject_cast<Cell*>(sender())->get_chip()->color)
                                                 )
                                         );
                }
                qobject_cast<Cell*>(sender())->deactivate();
            }
        }
    }
}

void Field::createWindow()
{
    this->setWindowTitle(QString("Dots"));
    this->setFixedSize(cols * (CHIP_RADIUS + SPACE) + 30, rows * (CHIP_RADIUS + SPACE) + 30);    // Фиксируем размеры виджета(окна)
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    grid = new QGridLayout();
    grid->setSpacing(SPACE);
    grid->setContentsMargins(15, 15, 15, 15);
    //grid->setContentsMargins(SPACE, SPACE, SPACE, SPACE);




    cell_matrix = new Cell**[rows];
    for(size_t i = 0; i < rows; i++)
    {
        cell_matrix[i] = new Cell*[cols];
        for (size_t j = 0; j < cols; j++)
        {
            cell_matrix[i][j] = new Cell();
            connect(cell_matrix[i][j], &Cell::signal1,this, &Field::slotFromChip);
            grid->addWidget(cell_matrix[i][j], i,j);
        }
    }

    this->setLayout(grid);
}

void Field::complete_combination()
{
    unsigned int score = 0;
    while(!combination.isEmpty())
    {
        //QMessageBox::information(this, "", QString("random " + QString::number(combination.count()) + " chip"));
        score += combination.last()->get_chip()->points;
        combination.last()->random_chip();
        combination.takeLast()->deactivate();
    }
    QMessageBox::information(this, "", QString("Combination score: " + QString::number(score) + " points"));
    combination.clear();
}

bool Field::adjacency_check(Cell *added)
{
    size_t i = 0;
    size_t j = 0;
    bool found = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (cell_matrix[i][j] == combination.last())
            {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    //up
    if (i > 0 && added == cell_matrix[i - 1][j]) return 1;
    //down
    if (i < rows - 1 && added == cell_matrix[i + 1][j]) return 1;
    //left
    if (j > 0 && added == cell_matrix[i][j - 1]) return 1;
    //right
    if (j < cols - 1 && added == cell_matrix[i][j + 1]) return 1;
    //cell_matrix[i][j]
    if (added == cell_matrix[i][j]) return 1;//если щелкнули на последнюю фишку
    return 0;
}
