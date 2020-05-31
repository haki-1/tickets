#include <iostream>
#include "cli.h"
#include "hall.h"
#include "event.h"


int main()
{
    CommandLineInterface cli;
    std::vector<Hall> halls;
    std::vector<Event> events;
    std::string command;
    while (true)
    {
        std::cin >> command;
        cli.setCommand(command);
        cli.executeCommand(halls, events);
    }
}