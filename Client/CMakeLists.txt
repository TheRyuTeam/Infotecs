cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

add_executable(Client
    src/Client.h
    src/Client.cpp
    src/main.cpp
)
target_link_libraries(Client
    PRIVATE
        Library
)
