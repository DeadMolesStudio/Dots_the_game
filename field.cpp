#include "field.h"

Field::Field(size_t rows, size_t cols) :
    rows(rows), cols(cols)
{
    cell_matrix = new Cell**[rows];
    for(size_t i = 0; i < rows; i++)
    {
        cell_matrix[i] = new Cell*[cols];
        for (size_t j = 0; j < cols; j++)
        {
            cell_matrix[i][j] = new Cell();
        }
    }
}

Cell* Field::get_cell(size_t row, size_t col)
{
    return cell_matrix[row][col];
}

void Field::random_field()
{
    for(size_t i = 0; i < rows; i++)
        {
        for(size_t j = 0; j < cols; j++)
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
    while(true)
    {
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = (i % 2); j < cols-2; j+=2)
            {
               if(check_cell(i, j)) return;
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

//void Field::update_field()
//{
//    for (size_t temp_col = 0; temp_col < cols; temp_col++)
//    {
//        int temp_row = rows - 1; // последняя строка
//        while (Cell* temp_empty_cell = get_empty_cell(temp_col, temp_row) != nullptr)
//        {
//            Cell* temp_not_empty_cell = get_not_empty_cell(temp_col, temp_row);
//            if (temp_not_empty_cell == nullptr)
//                get_empty_cell->random_chip();
//            else
//            {
//                temp_empty_cell->get_chip() = temp_not_empty_cell->get_chip();
//                temp_not_empty_cell->get_chip() = nullptr;
//            }
//        }
//    }
//}

//Cell* Field::get_empty_cell(size_t temp_col, size_t& temp_row)
//{
//    for (int i = temp_row; i > -1; i--)
//    {
//        if (cell_matrix[temp_col][i].get_chip() == nullptr)
//        {
//            if (cell_matrix[temp_col][i].is_blocked())
//                continue;
//            temp_row = i;
//            return &cell_matrix[temp_col][temp_row];
//        }
//    }
//    return nullptr;
//}

//Cell* Field::get_not_empty_cell(size_t temp_col, size_t& temp_row)
//{
//    for (int i = temp_row; i > -1; i--)
//    {
//        if (cell_matrix[temp_col][i].get_chip() != nullptr)
//        {
//            return &cell_matrix[temp_col][temp_row];
//        }
//    }
//    return nullptr;
//}

void Field::start_combination(Cell *first)
{
    return;
}

Field::~Field()
{
    for (int i = 0; i < rows; i++)
    {
        delete [] cell_matrix[i];
    }
    delete [] cell_matrix;
    combination.clear();
}
