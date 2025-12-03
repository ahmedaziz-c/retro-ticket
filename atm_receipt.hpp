#pragma once
#include <ftxui/dom/elements.hpp>

namespace atm {
    ftxui::Element header(const std::string& title);
    ftxui::Element row(const std::string& left, const std::string& right = "");
    ftxui::Element footer(const std::string& text = "");
}