#pragma once
#include <string>

struct Ticket
{
    int         id = 0;
    std::string title;
    int         status = 0;   // 0 todo, 1 done
    std::string created;
};