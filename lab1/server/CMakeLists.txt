cmake_minimum_required(VERSION 3.15)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_BINARY_DIR})

add_executable(server main.cpp listener.h mySocket.h  mainwindow.cpp mainwindow.h mySocket.cpp listener.cpp handler.cpp handler.h config.h connecter.cpp connecter.h listenHandler.cpp listenHandler.h)
target_link_libraries(server Qt5::Widgets)