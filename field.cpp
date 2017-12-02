#include "field.h"
#include "ui_field.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Field::Field(QWidget *,size_t rows, size_t cols) :
    rows(rows), cols(cols)
{
    createWindow();
    setMouseTracking(false);
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
            for (size_t j = (i % 2) + 1; j < cols-2; j+=2)
            {
               if (check_cell(i, j))
               {
                   repaint_field();
                   return;
               }
            }
        }
        qDebug() << "Mother, I'm RANDOMED";
        random_field();
    }
}

void Field::repaint_field()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
           cell_matrix[i][j]->repaint();
        }
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

void Field::createWindow()
{
    this->setFixedSize(cols * (CHIP_RADIUS + SPACE) + 30, rows * (CHIP_RADIUS + SPACE) + 30);    // Фиксируем размеры виджета(окна)
    QPalette Pal(palette());
    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, QColor(QRgb(0xe6e6fa)));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    grid = new QGridLayout();
    grid->setSpacing(SPACE);
    grid->setContentsMargins(15, 15, 15, 15);

    cell_matrix = new Cell**[rows];
    for(size_t i = 0; i < rows; i++)
    {
        cell_matrix[i] = new Cell*[cols];
        for (size_t j = 0; j < cols; j++)
        {
            cell_matrix[i][j] = new Cell();
//            connect(cell_matrix[i][j], &Cell::signal1,this, &Field::slotFromChip);
            connect(cell_matrix[i][j], &Cell::pressSignal,this, &Field::pressSlot);
            connect(cell_matrix[i][j], &Cell::leaveSignal,this, &Field::leaveSlot);
            connect(cell_matrix[i][j], &Cell::enterSignal,this, &Field::enterSlot);
            connect(cell_matrix[i][j], &Cell::releaseSignal,this, &Field::releaseSlot);
            connect(cell_matrix[i][j], &Cell::moveSignal,this, &Field::moveSlot);

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
        score += combination.last()->get_chip()->points;
        combination.last()->random_chip();
        combination.takeLast()->deactivate();
    }
    //QMessageBox::information(this, "", QString("Combination score: " + QString::number(score) + " points"));
    emit plusScore(score);
    combination.clear();
    //qDebug("COMPLETE_COMBINATION");
    check_field();
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

void Field::pressSlot()
{
    //qDebug("PRESS_SLOT");
    if(combination.isEmpty())
    {
    //если первая фишка в комбинации
      //  qDebug("первая фишка в комбинации");
        qobject_cast<Cell*>(sender())->activate();
        combination.append( qobject_cast<Cell*>(sender()) );
    }
    //тк нажатие происходит только один раз за комбинацию,
    //значит тут будет происходить добавление первой фишки в вектор и отрисовка выделения
}

void Field::moveSlot(QPoint mouse_pos)
{
    //qDebug("MOVE_SLOT");
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            //qDebug("in forfor");
            if (cell_matrix[i][j]->rect().contains(cell_matrix[i][j]->mapFromGlobal(mouse_pos)))
            {

//                qDebug("in if {...}");
         //       QString temp = QString("i = " + QString::number(i) + " j = " + QString::number(j));
           //     qDebug() << temp;/*temp.toStdString().c_str());*/
                add_to_combination(cell_matrix[i][j]);
//                qDebug() << "end MOVE_SLOT";
                return;
                //break;
            }
            else
            {
                //qDebug("else {...}");
            }
        }
    }
//    qDebug() << "end MOVE_SLOT";
}

void Field::releaseSlot()
{
   // qDebug("RELEASE_SLOT");
    if (combination.count() == 1)
    {
     //   qDebug("только одна фишка в кобинации - отмена");
        qobject_cast<Cell*>(sender())->deactivate();
        combination.clear();
    }
    else
    {
       // qDebug("комбинация завершена");
        complete_combination();
    }

    //отпускание будет также происходить по завершении комбинации,
    //но возможен вариант, что мы отпускаем, когда только одна фишка в векторе
    //проверяем наличие комбинаций на поле
}

void Field::leaveSlot()
{
   // qDebug("LEAVE_SLOT");
//    if (qobject_cast<Cell*>(sender()) == )
    //здесь надо проверять нажата ли мышь в данный момент(?)
    //или проверять, есть ли текущая комбинация(?)
    //если фишка, область которой мы покинули, нам подходит(т.е проверяем все условия)
    //то добавляем ее в вектор
    //иначе ничего не делаем
}

void Field::add_to_combination(Cell* added)
{
   // qDebug("ADD_TO_COMBINATION");

    if(combination.isEmpty())
    {
     //   qDebug() << "IM EMPTY";
        return;
    }
    if (added->get_chip()->color == combination.last()->get_chip()->color)
            //если цвет совпадает

    {
        if ( adjacency_check(added) )
        {
            if (added != combination.last())
            {
               if (combination.count() > 1 && added == combination[combination.count() - 2])
               {
                   //qDebug("тупо минус фишка");
                   combination.takeLast()->deactivate();
                   //qDebug() << "вы навели куда надо";
                   return;
               }
               if ( !added->is_in_combination() )
               {
                   combination.append( added );
                   added->activate();
     //              qDebug("фишка добавлена в комбинацию");
               }
               else
               {
       //            qDebug("фишка уже в кобинации - отмена");
                   added->activate();
               }
            }
            else
            {
//                qDebug() << "вы навели на last()";
                //combination.clear();
                //вот тут отменяем анимацию последней
            }
        }
        else
        {
         //   qDebug("фишка не соседняя");
            if (!added->is_in_combination())
            {
                added->deactivate();
            }
        }
    }
    else //цвет не совпадает
    {
        if ( adjacency_check(qobject_cast<Cell*>(sender())) )
        {
           // qDebug("фишка не подходит по цвету");
            added->deactivate();
        }
    }
}

void Field::enterSlot()
{
//    qDebug("ENTER_SLOT");
    if(combination.isEmpty())
    {
    //    qDebug() << "endof ENTER_SLOT";
        return;
    }
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
                   qobject_cast<Cell*>(sender())->activate();
      //             qDebug("фишка добавлена в комбинацию");
               }
               else
               {
        //           qDebug("фишка уже в кобинации - отмена");
                   qobject_cast<Cell*>(sender())->activate();
               }
            }
            else
            {
          //      qDebug("только одна фишка в кобинации - отмена");
                qobject_cast<Cell*>(sender())->deactivate();
                combination.clear();
                //вот тут отменяем анимацию последней
            }
        }
        else
        {
        //   qDebug("фишка не соседняя");
           qobject_cast<Cell*>(sender())->deactivate();
        }
    }
    else //цвет не совпадает
    {
        if ( adjacency_check(qobject_cast<Cell*>(sender())) )
        {
          //  qDebug("фишка не подходит по цвету");
            qobject_cast<Cell*>(sender())->deactivate();
        }
        else
        {
            //qDebug("фишка не подходит по цвету");
            qobject_cast<Cell*>(sender())->deactivate();
        }
    }
    //проверяем, нажата ли мышь
    //проверка по всем параметрам фишки
    //если фишка такая же, как и предыдущая, то вычеркиваем последнюю из комбинации и отменяем ее выделение
    //если подходит, то отрисовываем выделение, добавляем в вектор
    //??
    //qDebug() << "endof ENTER_SLOT";
}
