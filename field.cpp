#include "field.h"
#include "ui_field.h"

const int CHIP_RADIUS = 25;
const int SPACE = 5;

Field::Field(QWidget *,size_t rows, size_t cols) :
    rows(rows), cols(cols)
{
    createWindow();
    setMouseTracking(true);
}

Cell* Field::get_cell(size_t row, size_t col)
{
    return cell_matrix[row][col];
}

bool Field::cell_position(Cell *cell, size_t &row, size_t &col)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (cell_matrix[i][j] == cell)
            {
                row = i;
                col = j;
                return 1;
            }
        }
    }
    return 0;
}

void Field::random_field()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (!cell_matrix[i][j]->is_blocked())
            {
                cell_matrix[i][j]->animated_random_chip();
            }
        }
    }
}

void Field::check_field()//проверяет наличие комбинаций на поле(шахматный порядок(чекнуть в случае с вырезами у краев))
{
    while (true)
    {
//        for (size_t i = 0; i < rows; i++)
//        {
//            for (size_t j = (i % 2) + 1; j < cols-2; j+=2)
//            {
//               if (check_cell(i, j))
//               {
//                   //repaint_field();
//                   return;
//               }
//            }
//        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                if (check_cell(i, j))
                {
                    //repaint_field();
                    return;
                 }
             }
        }

        qDebug() << "Mother, I'm RANDOMED";
        random_field();
        repaint_field();
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
        if (cell_matrix[row-1][col]->get_chip()->color == cell_matrix[row][col]->get_chip()->color && !cell_matrix[row-1][col]->is_blocked()) return 1;
    }
    //down
    if(row < rows - 1)
    {
        if (cell_matrix[row+1][col]->get_chip()->color == cell_matrix[row][col]->get_chip()->color  && !cell_matrix[row+1][col]->is_blocked()) return 1;
    }
    //left
    if(col > 1)
    {
        if (cell_matrix[row][col-1]->get_chip()->color == cell_matrix[row][col]->get_chip()->color  && !cell_matrix[row][col - 1]->is_blocked()) return 1;
    }
    //right
    if(col < cols - 1)
    {
        if (cell_matrix[row][col+1]->get_chip()->color == cell_matrix[row][col]->get_chip()->color  && !cell_matrix[row][col + 1]->is_blocked()) return 1;
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

void Field::random_field_bonus()
{
    qDebug() << "random_field_bonus";
    random_field();
    check_field();
}

void Field::line_destroy_bonus(size_t number)
{
    emit add_extra_move();
    qDebug() << "line_destroy_bonus";
    for (size_t j = 0; j < cols; j++)
    {
        cell_matrix[number][j]->activate();
        combination.append(cell_matrix[number][j]);
    }
    uint score = 0;
    while(!combination.isEmpty())
    {
        score += combination.last()->get_chip()->points;
        emit check_reqs_for_cell(*(combination.last()->get_chip()));
        combination.last()->animated_random_chip();
        combination.takeLast()->deactivate();
    }
    emit plusScore(score);
    combination.clear();
    //qDebug("COMPLETE_COMBINATION");
    check_field();
}

void Field::color_bonus()
{
    emit add_extra_move();
    qDebug() << "color_bonus";
    Cell *temp = new Cell();
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (cell_matrix[i][j]->get_chip()->color == temp->get_chip()->color)
            {
                combination.append(cell_matrix[i][j]);
            }
        }
    }
    uint score = 0;
    for (size_t i = 0; i < combination.count(); i++)
    {
        score += combination[i]->get_chip()->points;
        emit check_reqs_for_cell(*(combination.last()->get_chip()));
        combination[i]->activate();
        QTimer::singleShot(800, combination[i], &Cell::animated_random_chip);
        QTimer::singleShot(780, combination[i],&Cell::deactivate);
    }
    emit plusScore(score);
    combination.clear();
    //qDebug("COMPLETE_COMBINATION");
    check_field();
    delete temp;
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
            cell_matrix[i][j] = new Cell(this);
            connect(cell_matrix[i][j], &Cell::pressSignal,this, &Field::pressSlot);
            connect(cell_matrix[i][j], &Cell::releaseSignal,this, &Field::releaseSlot);
            connect(cell_matrix[i][j], &Cell::moveSignal,this, &Field::moveSlot);

            grid->addWidget(cell_matrix[i][j], i,j);
        }
    }

    this->setLayout(grid);
}

void Field::set_cell_blocked(size_t row, size_t col)
{
    cell_matrix[row][col]->block(true);
}

void Field::preset1()
{
    //I
    qDebug() << "preset1";
        set_cell_blocked(2,0);
        set_cell_blocked(3,0);
        set_cell_blocked(4,0);
        set_cell_blocked(2,6);
        set_cell_blocked(3,6);
        set_cell_blocked(4,6);
}

void Field::preset2()
{
    //звездочка
            set_cell_blocked(0,0);
            set_cell_blocked(1,0);
            set_cell_blocked(2,0);
            set_cell_blocked(0,1);
            set_cell_blocked(0,2);
            set_cell_blocked(1,1);


            set_cell_blocked(6,0);
            set_cell_blocked(5,0);
            set_cell_blocked(4,0);
            set_cell_blocked(6,1);
            set_cell_blocked(6,2);
            set_cell_blocked(5,1);


            set_cell_blocked(0,4);
            set_cell_blocked(0,5);
            set_cell_blocked(0,6);
            set_cell_blocked(1,6);
            set_cell_blocked(2,6);
            set_cell_blocked(1,5);


            set_cell_blocked(6,4);
            set_cell_blocked(6,5);
            set_cell_blocked(6,6);
            set_cell_blocked(5,6);
            set_cell_blocked(4,6);
            set_cell_blocked(5,5);
}

void Field::preset3()
{
            ///дырка
            set_cell_blocked(2,2);
            set_cell_blocked(2,3);
            set_cell_blocked(2,4);
            set_cell_blocked(3,3);
            set_cell_blocked(3,2);
            set_cell_blocked(3,4);
            set_cell_blocked(4,2);
            set_cell_blocked(4,3);
            set_cell_blocked(4,4);
}

void Field::complete_combination()
{
    unsigned int score = 0;
    if (combination.count() >= 5)
    {
        uint temp = quant();
        emit plusScore(temp);
        combination.clear();
        check_field();
        return;
    }
    emit not_quant();
    while(!combination.isEmpty())
    {
        score += combination.last()->get_chip()->points;
        emit check_reqs_for_cell(*(combination.last()->get_chip()));
        combination.last()->animated_random_chip();
        combination.takeLast()->deactivate();
    }
    emit plusScore(score);
    combination.clear();
    //qDebug("COMPLETE_COMBINATION");
    check_field();
}

void Field::complete_quadr_combination()
{
    unsigned int score = 0;
    emit not_quant();
    score += quadr();
//        TODO: вызывать ее в релизивенте вместо комплет в случае квадра
//                сюда надо вкопипастить все из комплита с учетом рандома фишек без старого цвета
    combination.takeLast();//чтобы последняя(она же первая) фишка не считалась дважды
    while(!combination.isEmpty())
    {
        score += combination.last()->get_chip()->points;
        emit check_reqs_for_cell(*(combination.last()->get_chip()));
        combination.last()->animated_random_chip();
        combination.last()->set_quadr_flag(false);
        combination.takeLast()->deactivate();
    }
    emit plusScore(score);
    combination.clear();
    //qDebug("COMPLETE_QUADR_COMBINATION");
    check_field();
}

bool Field::adjacency_check(Cell *added)
{
    if (added->is_blocked())
    {
        return false;
    }
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
        if (combination.count() == 5 && combination.last() == combination.first())
        {
            complete_quadr_combination();
        }
        else
        {
            complete_combination();
        }
    }
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
                   if (combination.count() == 5 && combination.last() == combination.first())
                   {
                       for (size_t i = 0; i < rows; i++)
                       {
                           for (size_t j = 0; j < cols; j++)
                           {
                               if (cell_matrix[i][j]->get_chip()->color == added->get_chip()->color && !cell_matrix[i][j]->is_in_quadr())
                               {
                                   cell_matrix[i][j]->deactivate();
                               }
                           }
                       }
                       combination.takeLast();
                   }
                   else
                   {
                       combination.takeLast()->deactivate();
                   }
                   //qDebug() << "вы навели на предыдущую фишку - отмена последней фишки";
                   return;
               }
               if ( !added->is_in_combination() )
               {
                   if (combination.count() == 5 && combination.last() == combination.first())
                   {
                       qDebug() << "вы пытаетесь обузить очки, сэр";
                       added->deactivate();
                   }
                   else
                   {
                   combination.append( added );
                   added->activate();
     //              qDebug("фишка добавлена в комбинацию");
                   }
               }
               else
               {
       //            qDebug("фишка уже в кобинации - отмена");
                   added->activate();
                   if (combination.count() == 4 && added == combination.first())
                   {
                       qDebug() << "квадрик найден";
                       for (size_t i = 0; i < combination.count(); i++)
                       {
                           combination[i]->set_quadr_flag(true);
                       }
                       combination.append( added );
                       for (size_t i = 0; i < rows; i++)
                       {
                           for (size_t j = 0; j < cols; j++)
                           {
                               if (cell_matrix[i][j]->get_chip()->color == added->get_chip()->color)
                               {
                                   cell_matrix[i][j]->activate();//may be only graphics activate?
                               }
                           }
                       }
                       //анимашка в видел часиков
                       return;
                   }
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

unsigned int Field::quadr()
{
    qDebug() << "quadr";
    unsigned int local_score = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (cell_matrix[i][j]->get_chip()->color == combination.last()->get_chip()->color && !cell_matrix[i][j]->is_in_quadr())
            {
                local_score += cell_matrix[i][j]->get_chip()->points;
                emit check_reqs_for_cell(*(cell_matrix[i][j]->get_chip()));
                cell_matrix[i][j]->deactivate();
                cell_matrix[i][j]->animated_random_chip();
            }
        }
    }
    return local_score;
}

unsigned int Field::quant()
{
    qDebug() << "quant";
    unsigned int local_score = 0;
    emit quant_s(combination.last()->get_chip()->color);
    while(!combination.isEmpty())
    {
        local_score += combination.last()->get_chip()->points;
        emit check_reqs_for_cell(*(combination.last()->get_chip()));
        combination.last()->animated_random_chip();
        combination.takeLast()->deactivate();

    }
    return local_score;
}
