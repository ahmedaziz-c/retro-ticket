#include <ftxui/screen/screen.hpp>
#include <ftxui/component/loop.hpp>
#include "database.hpp"
#include "dashboard.hpp"
#include "fkey_hook.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: retro-ticket project.db\n";
        return 1;
    }
    try {
        db::open(argv[1]);
        fkey_hook::install();      // steal F1-F12
        auto screen = ftxui::ScreenInteractive::Fullscreen();
        Dashboard dash(screen);
        screen.Loop(dash.renderer());
    } catch (const std::exception& ex) {
        std::cerr << "Fatal: " << ex.what() << '\n';
        return 2;
    }
}