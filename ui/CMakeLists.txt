cmake_minimum_required(VERSION 3.19)
project(TriangleMatrixUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(TriangleMatrixUI
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    firework.h
)

target_include_directories(TriangleMatrixUI PRIVATE
    /Users/yana/Desktop/lab3
)

target_link_libraries(TriangleMatrixUI
    PRIVATE
        Qt::Core
        Qt::Widgets
)