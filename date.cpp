#include "date.h"

Date stringToDate(std::string str)
{
    std::string year = str.substr(0, 4);
    std::string mon = str.substr(5, 2);
    std::string mday = str.substr(8, 2);
    return {(unsigned short)std::stoul(mday), (unsigned short)std::stoul(mon), (unsigned short)std::stoul(year)};
}