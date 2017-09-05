cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

file(GLOB Q3MENUS_LIB_SOURCE src/*.cpp)

add_library(q3menus STATIC ${Q3MENUS_LIB_SOURCE})

target_include_directories(q3menus PUBLIC include)