#include "requirement.h"

Requirement::Requirement(Chip sample, size_t demand)
    : demand(demand)
{
    this->sample = Chip(sample.shape, sample.color);
    current = 0;
}

bool Requirement::check(Chip test)
{
    if (is_done() && test.shape == sample.shape && test.color == sample.color) return 0;
    if (test.shape == sample.shape && test.color == sample.color)
    {
        current++;
        return 1;
    }
    return 0;
}

bool Requirement::is_done()
{
   return current == demand ? true : false;
}

size_t Requirement::left()
{
    return demand - current;
}

Requirement::~Requirement()
{

}

Chip Requirement::get_sample()
{
    return sample;
}


