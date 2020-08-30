cmake_minimum_required(VERSION 3.0.0)
project(GemWuenak VERSION 0.1.0)

include(CTest)
enable_testing()

option(DEBUG_MODE "DebugGame" OFF)
option(ASCII_FALLBACK "Fallback" OFF)
set(GAME_NAME "GemWuenak")

add_executable(GemWuenak main.cpp)
add_library(EXTRA_STUFF STATIC extras/extra.cpp)

add_library(FLAPPY_MENU STATIC flappy_bird/flappy_menu.cpp)
add_library(FLAPPY_GAME STATIC flappy_bird/flappygame.cpp)
add_library(FLAPPY_SCORE STATIC flappy_bird/highscore.cpp)

add_library(KARTU41 STATIC kartu41/kartu41.cpp)
add_library(KARTU41_MENU STATIC kartu41/kartu41_menu.cpp)

add_library(PONGGAME STATIC pong/ponggame.cpp)

target_link_libraries(GemWuenak EXTRA_STUFF)
target_link_libraries(GemWuenak FLAPPY_MENU)
target_link_libraries(GemWuenak FLAPPY_GAME)
target_link_libraries(GemWuenak FLAPPY_SCORE)

target_link_libraries(GemWuenak KARTU41)
target_link_libraries(KARTU41_MENU KARTU41)
target_link_libraries(GemWuenak KARTU41_MENU)
target_link_libraries(GemWuenak PONGGAME)

if(DEBUG_MODE)
    message(STATUS "Will build debug version")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DDEBUGAME")
    set(GAME_NAME "${GAME_NAME}_debugbuild")
    set_target_properties(GemWuenak PROPERTIES OUTPUT_NAME "${GAME_NAME}")
endif()
if(ASCII_FALLBACK)
    message(STATUS "Will build with ASCII Fallback")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DFALLBACKASCII")
    set(GAME_NAME "${GAME_NAME}_fallback")
    set_target_properties(GemWuenak PROPERTIES OUTPUT_NAME "${GAME_NAME}")
endif()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O1 -s")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
