#include "dashboard.hpp"
#include "atm_receipt.hpp"
#include "database/database.hpp"
#include "palette.hpp"
#include <ftxui/dom/table.hpp>

using namespace ftxui;

Dashboard::Dashboard(ScreenInteractive& s)
{
    auto tickets = db::load_tickets();
    std::vector<std::vector<std::string>> data = { {"ID","Title","Status"} };
    for (const auto& t : tickets)
        data.push_back({ std::to_string(t.id), t.title, std::to_string(t.status) });

    auto table = Table(data);
    table.SelectAll().Border(LIGHT);   // 1-pixel rule
    table.SelectColumn(0).Border(LIGHT);
    table.SelectColumn(1).Border(LIGHT);
    table.SelectColumn(2).Border(LIGHT);

    container_ = Renderer([&] {
        return vbox({
            atm::header(" RETRO-TICKET "),
            table.Render() | flex,
            atm::footer(" F2=new  F3=edit  F4=del  Q=quit ")
        }) | bgcolor(Pal::black);
    });
}

Component Dashboard::renderer() { return container_; }
