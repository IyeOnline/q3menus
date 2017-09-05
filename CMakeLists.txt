cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(q3menu VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -Wno-ignored-qualifiers -fdiagnostics-color=always")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -march=native")
endif()

add_subdirectory(q3menus)

option(Q3MENUS_BUILD_TESTS "Enables the test suite targets" ON)
if(Q3MENUS_BUILD_TESTS)
	add_subdirectory(demo demo)
endif()