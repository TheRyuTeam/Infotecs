cmake_minimum_required(VERSION 3.16)

project(Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(Client
    src/Client.h
    src/Client.cpp
    src/main.cpp
)
target_link_libraries(Client
    PRIVATE
        Library
        Threads::Threads
)
