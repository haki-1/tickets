#pragma once
#include <string>
#include <vector>
#include "hall.h"

struct Date
{
    unsigned short mday, mon, year;
};

class Event
{
public:
    enum SeatStatus{ free, booked, bought };
    struct Note
    {
        size_t row, seat;
        std::string note;
    };
    
    Event(Date _date, Hall* _hall, std::string _name);
    Event(Date _date, Hall* _hall, std::string _name, SeatStatus** _seats);
    Date getDate();
    Hall* getHall();
    std::string getName();
    SeatStatus** getSeats();
    std::vector<Note> &getNotes();
    ~Event();

private:
    Date date;
    Hall* hall;
    std::string name;
    SeatStatus** seats;
    std::vector<Note> notes;
};