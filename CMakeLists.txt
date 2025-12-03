cmake_minimum_required(VERSION 3.25)
project(retro-ticket LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
find_package(ftxui REQUIRED)
find_package(Threads REQUIRED)

add_executable(retro-ticket
    retro-ticket.cpp
    database/database.cpp
    ui/atm_receipt.cpp
    ui/dashboard.cpp
    input/fkey_hook_win32.cpp   # or _x11.cpp on Linux
)

target_link_libraries(retro-ticket PRIVATE ftxui::screen ftxui::dom ftxui::component Threads::Threads)
target_compile_options(retro-ticket PRIVATE /W4 /WX)  # -Wall -Wextra -Werror on gcc/clang
install(TARGETS retro-ticket DESTINATION bin)
