#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "hall.h"
#include "event.h"

class CommandLineInterface
{
public:
    CommandLineInterface();
    void setCommand(std::string _command);
    void executeCommand(std::vector<Hall>& halls, std::vector<Event>& events);
    ~CommandLineInterface();

private:
    std::string command;
    std::string openedFile;
    void open(std::vector<Hall>& halls, std::vector<Event>& events);
    void close(std::vector<Hall>& halls, std::vector<Event>& events);
    void save(std::vector<Hall>& halls, std::vector<Event>& events);
    void saveas();
    void help();
    void exit();

    void addevent(std::vector<Hall>& halls, std::vector<Event>& events);
    void freeseats(std::vector<Event>& events);
    void book(std::vector<Event>& events);
    void unbook(std::vector<Event>& events);
};