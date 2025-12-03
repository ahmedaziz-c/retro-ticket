#pragma once
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>

class Dashboard {
public:
    Dashboard(ftxui::ScreenInteractive& s);
    ftxui::Component renderer();
private:
    ftxui::Component container_;
};