#include "atm_receipt.hpp"
#include "palette.hpp"
#include <sstream>

using namespace ftxui;

Element atm::header(const std::string& title)
{
    std::ostringstream oss;
    oss << "  " << title << "  ";
    return text(oss.str()) | bold | color(Pal::green) | bgcolor(Pal::black);
}

Element atm::row(const std::string& left, const std::string& right)
{
    std::ostringstream oss;
    oss << left;
    if (!right.empty()) {
        int pad = 50 - left.size() - right.size();
        if (pad > 0) oss << std::string(pad, ' ');
        oss << right;
    }
    return text(oss.str()) | color(Pal::white) | bgcolor(Pal::black);
}

Element atm::footer(const std::string& text)
{
    return ftxui::text(text) | dim | color(Pal::dim_amber) | bgcolor(Pal::black);
}