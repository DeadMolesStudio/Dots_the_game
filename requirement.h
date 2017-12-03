#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include "chip.h"
#include <QDebug>

class Requirement
{
public:
    Requirement(Chip sample = Chip(0,0), size_t demand = 0);
    bool check(Chip test);
    bool is_done();
    Chip get_sample();
    size_t left();
    ~Requirement();
private:
    Chip sample;
    size_t current;
    size_t demand;
};

#endif // REQUIREMENT_H
