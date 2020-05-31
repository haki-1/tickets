#include "hall.h"

Hall::Hall(size_t _number, size_t _rows, size_t _seatsInRow) : number(_number), rows(_rows), seatsInRow(_seatsInRow) {}

size_t Hall::getNumber()
{
    return number;
}

size_t Hall::getRows()
{
    return rows;
}

size_t Hall::getSeatsInRow()
{
    return seatsInRow;
}