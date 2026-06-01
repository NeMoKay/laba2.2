cmake_minimum_required(VERSION 3.19)
project(ui_ui)

set(CMAKE_CXX_STANDARD 23)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


qt_standard_project_setup() 

qt_add_executable(ui_ui WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
)


target_include_directories(ui_ui PRIVATE ../include .)


target_link_libraries(ui_ui PRIVATE Qt6::Core Qt6::Widgets)