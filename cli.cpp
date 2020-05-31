#include "cli.h"

CommandLineInterface::CommandLineInterface() : command(""), openedFile("") {}

void CommandLineInterface::setCommand(std::string _command)
{
    command = _command;
}

void CommandLineInterface::executeCommand(std::vector<Hall>& halls, std::vector<Event>& events)
{
    if(command == "open") open(halls, events);
    if(command == "close") close(halls, events);
    if(command == "save") save(halls, events);
    if(command == "saveas") saveas();
    if(command == "help") help();
    if(command == "exit") exit();
    if(command == "addevent") addevent(halls, events);
    if(command == "freeseats") freeseats(events);
    if(command == "book") book(events);
    if(command == "unbook") book(events);

}

CommandLineInterface::~CommandLineInterface() {}

Date stringToDate(std::string str)
{
    std::string year = str.substr(0, 4);
    std::string mon = str.substr(5, 2);
    std::string mday = str.substr(8, 2);
    return {(unsigned short)std::stoul(mday), (unsigned short)std::stoul(mon), (unsigned short)std::stoul(year)};
}

std::string dateToString(Date date)
{
    std::string str = std::to_string(date.year);
    str += "-";
    str += std::to_string(date.mon);
    str += "-";
    str += std::to_string(date.mday);
    return str;

}

void CommandLineInterface::open(std::vector<Hall>& halls, std::vector<Event>& events)
{
    std::string currFile;
    std::cin >> currFile;
    std::ifstream file(currFile);
    if(file)
    {
        file >> std::ws;
        do
        {
            char c;
            file.get(c);
            if(c == 'h')
            {
                size_t number, rows, seatsInRow;
                file >> number >> std::ws >> rows >> std::ws >> seatsInRow;
                halls.push_back({number,rows, seatsInRow});
            }
            if(c == 'e')
            {
                std::string date, name;
                size_t numberHall;
                Hall* hallPtr = nullptr;
                file >> date >> std::ws >> numberHall >> std::ws >> name >> std::ws;
                for (Hall h : halls)
                {
                    if(numberHall == h.getNumber()) hallPtr = &h;
                }
                size_t rows = hallPtr->getRows();
                size_t seatsInRow = hallPtr->getSeatsInRow();
                Event::SeatStatus** seats = new Event::SeatStatus*[rows];
                for (size_t i = 0; i < rows; ++i)
                {
                    seats[i] = new Event::SeatStatus[seatsInRow];
                    for (size_t j = 0; j < seatsInRow; ++j)
                    {
                        size_t status;
                        file >> status;
                        seats[i][j] = (Event::SeatStatus)status;
                    }
                }
                events.push_back({stringToDate(date), hallPtr, name, seats});
            }
            file >> std::ws;
        } while (!file.eof());
        openedFile = currFile;
        std::cout << "Successfully opened " << currFile << std::endl;
    }
}

void CommandLineInterface::close(std::vector<Hall>& halls, std::vector<Event>& events)
{
    halls.clear();
    events.clear();
    openedFile = "";
}

void CommandLineInterface::save(std::vector<Hall>& halls, std::vector<Event>& events)
{
    std::ofstream file(openedFile);
    if(file)
    {
        for (Hall h : halls)
        {
            file << "h " << h.getNumber() << " " << h.getRows() << " " << h.getSeatsInRow() << " ";
        }
        for (Event e : events)
        {
            file << "e " << dateToString(e.getDate()) << " " << e.getHall()->getNumber() << " " << e.getName() << " ";
            size_t rows = e.getHall()->getRows();
            size_t seatsInRow = e.getHall()->getSeatsInRow();
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < seatsInRow; ++j)
                {
                    file << (size_t)e.getSeats()[i][j];
                }
            }
        }
    }
}

void CommandLineInterface::saveas()
{

}

void CommandLineInterface::help()
{

}

void CommandLineInterface::exit()
{

}

void addevent(std::vector<Hall>& halls, std::vector<Event>& events)
{
    std::string strDate, name;
    size_t numberHall;
    std::cin >> strDate >> numberHall >> name;
    Hall *hallPtr = nullptr;
    for (Hall h : halls)
    {
        if(numberHall == h.getNumber()) hallPtr = &h;
    }
    bool free = true;
    Date date = stringToDate(strDate);
    for (Event e : events)
    {
        Date currDate = e.getDate();
        if(numberHall == e.getHall()->getNumber() && date.year == currDate.year && date.mon == currDate.mon && date.mday == currDate.mday) free = false;
    }
    if(free) events.push_back({date, hallPtr, name});
    else std::cout << "There is already another performance in this hall on the same date!";
}

void freeseats(std::vector<Event>& events)
{
    std::string strDate, name;
    std::cin >> strDate >> name;
    Date date = stringToDate(strDate);
    for (Event e : events)
    {
        Date currDate = e.getDate();
        if(name == e.getName() && date.year == currDate.year && date.mon == currDate.mon && date.mday == currDate.mday)
        {
            size_t rows = e.getHall()->getRows();
            size_t seatsInRow = e.getHall()->getSeatsInRow();
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < seatsInRow; ++j)
                {
                    if(e.getSeats()[i][j] == Event::SeatStatus::free)
                    {
                        std::cout << "Row: " << i << ", Seat: " << j << std::endl;
                    }
                }
            }
        }
    }
}

void book(std::vector<Event>& events)
{
    size_t row, seat;
    std::string strDate, name, note;
    std::cin >> row >> seat >> strDate >> name >> note;
    Date date = stringToDate(strDate);
    for (Event e : events)
    {
        Date currDate = e.getDate();
        if(name == e.getName() && date.year == currDate.year && date.mon == currDate.mon && date.mday == currDate.mday)
        {
            e.getSeats()[row][seat] = Event::SeatStatus::booked;
            e.getNotes().push_back({row, seat, note});
        }
    }
}

void unbook(std::vector<Event>& events)
{
    size_t row, seat;
    std::string strDate, name;
    std::cin >> row >> seat >> strDate >> name;
    Date date = stringToDate(strDate);
    for (Event e : events)
    {
        Date currDate = e.getDate();
        if(name == e.getName() && date.year == currDate.year && date.mon == currDate.mon && date.mday == currDate.mday)
        {
            e.getSeats()[row][seat] = Event::SeatStatus::free;
            for (size_t i = 0; i < e.getNotes().size(); ++i)
            {
                if(row == e.getNotes()[i].row && seat == e.getNotes()[i].seat)
                {
                    e.getNotes().erase(e.getNotes().begin() + i);
                }
            }
        }
    }    
}