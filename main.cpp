#include <iostream>

int main() {


    return 0;
}

void update_field() { // лежит в Field
    for (size_t temp_col = 0; temp_col < cols; temp_col++) {
        int temp_row = rows - 1; // последняя строка
        while (Cell* temp_empty_cell = get_empty_cell(temp_col, temp_row) != nullptr) {
            Cell* temp_not_empty_cell = get_not_empty_cell();
            if (temp_not_empty_cell == nullptr)
                get_empty_cell->random_chip();
            else {
                temp_empty_cell->get_chip() = temp_not_empty_cell->get_chip();
                temp_not_empty_cell->get_chip() = nullptr;
            }
        }
    }
}

Cell* get_empty_cell(size_t temp_col, size_t& temp_row) { // Field
    for (int i = temp_row; i > -1; i--) {
        if (cell_matrix[temp_col][i].get_chip() == nullptr) {
            if (cell_matrix[temp_col][i].is_blocked())
                continue;
            temp_row = i;
            return &cell_matrix[temp_col][temp_row];
        }
    }
    return nullptr;
}

Cell* get_not_empty_cell(size_t temp_col, size_t& temp_row) { // Field
    for (int i = temp_row; i > -1; i--) {
        if (cell_matrix[temp_col][i].get_chip() != nullptr) {
            return &cell_matrix[temp_col][temp_row];
        }
    }
    return nullptr;
}