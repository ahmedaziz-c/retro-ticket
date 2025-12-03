cmake_minimum_required(VERSION 3.25)
project(retro-ticket LANGUAGES CXX)

# VS2022 + vcpkg friendly
find_package(ftxui CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_executable(retro-ticket
    retro-ticket.cpp
    database.cpp
    atm_receipt.cpp
    dashboard.cpp
    fkey_hook_win32.cpp
)

target_link_libraries(retro-ticket PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    Threads::Threads
)

# VS warning level 4
if(MSVC)
    target_compile_options(retro-ticket PRIVATE /W4 /WX)
endif()

# Ctrl-F5 launches full-screen
set_target_properties(retro-ticket PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
