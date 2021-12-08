cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tetris VERSION 1.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(tetris src/main.c)
target_link_libraries(tetris ${CURSES_LIBRARIES})
target_include_directories(tetris PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)