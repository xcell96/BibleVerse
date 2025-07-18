cmake_minimum_required(VERSION 4.0)
project(BibleVerse)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SWORD REQUIRED sword)

include_directories(${SWORD_INCLUDE_DIRS})
link_directories(${SWORD_LIBRARY_DIRS})

add_executable(BibleVerse main.cpp
        src/InputParser.cpp
        src/InputParser.h
        src/TextFetcher.cpp
        src/TextFetcher.h)

target_link_libraries(BibleVerse ${SWORD_LIBRARIES})