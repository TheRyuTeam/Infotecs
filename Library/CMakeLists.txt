cmake_minimum_required(VERSION 3.16)

project(Library VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(Library SHARED
    include/Library/LibraryExports.h
    include/Library/Library.h
    include/Library/Endpoint.h
    include/Library/UDPSocket.h

    src/Library.cpp
    src/Endpoint.cpp
    src/UDPSocket.cpp
)
target_compile_definitions(Library
    PRIVATE LIBRARY_EXPORTS
)
target_include_directories(Library
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
