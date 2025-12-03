#pragma once
#include <string>
#include <vector>
#include "models/ticket.hpp"

namespace db {
    void open(const std::string& file);
    void close();
    std::vector<Ticket> load_tickets();
    int  insert_ticket(const std::string& title);
    void update_ticket_status(int id, int status);
}
