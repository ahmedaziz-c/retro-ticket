// retro-ticket.cpp – entry point, full screen, owns F-keys
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/loop.hpp"
#include "database/database.hpp"   // our slim wrapper
#include "ui/atm_receipt.hpp"
#include "ui/dashboard.hpp"
#include "input/fkey_hook.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: retro-ticket project.db\n";
        return 1;
    }
    try {
        db::open(argv[1]);               // creates if absent
        fkey_hook::install();            // eat F1-F12
        auto screen = ftxui::ScreenInteractive::Fullscreen();
        Dashboard dash(screen);
        screen.Loop(dash.renderer());
    } catch (const std::exception& ex) {
        std::cerr << "Fatal: " << ex.what() << '\n';
        return 2;
    }
}
