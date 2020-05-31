#include "event.h"

Event::Event(Date _date, Hall* _hall, std::string _name) : 
date(_date), hall(_hall), name(_name), seats(new SeatStatus*[hall->getRows()]), notes({})
{
    size_t rows = hall->getRows();
    size_t seatsInRow = hall->getSeatsInRow();
    for (size_t i = 0; i < rows; ++i)
    {
        seats[i] = new SeatStatus[seatsInRow];
        for (size_t j = 0; j < seatsInRow; ++j)
        {
            seats[i][j] = free;
        }
    }
}

Event::Event(Date _date, Hall* _hall, std::string _name, SeatStatus** _seats) :
date(_date), hall(_hall), name(_name), seats(_seats), notes({}) {}

Date Event::getDate()
{
    return date;
}

Hall* Event::getHall()
{
    return hall;
}

std::string Event::getName()
{
    return name;
}

Event::SeatStatus** Event::getSeats()
{
    return seats;
}

std::vector<Event::Note> & Event::getNotes()
{
    return notes;
}

Event::~Event()
{

}