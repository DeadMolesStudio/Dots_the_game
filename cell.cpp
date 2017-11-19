#include "cell.h"

Cell::Cell()
{
    pointer_chip = new Chip();
}

Cell::Cell(Chip *chip, bool blocked) :
    blocked(blocked), pointer_chip(chip)
{

}

Chip* Cell::get_chip()
{
    return pointer_chip;
}

void Cell::random_chip()
{
    delete pointer_chip;
    pointer_chip  = new Chip();
}

bool Cell::is_blocked()
{
    return blocked;
}

Cell::~Cell()
{
    delete pointer_chip;
}
