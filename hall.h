#pragma once

#include <iostream>

class Hall
{
public:
    Hall(size_t number, size_t rows, size_t seatsInRow);
    size_t getNumber();
    size_t getRows();
    size_t getSeatsInRow();

private:
    size_t number, rows, seatsInRow;
};