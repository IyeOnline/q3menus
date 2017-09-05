add_executable(q3menus_demo src/main.cpp src/damagemenu.cpp)

target_link_libraries(q3menus_demo PRIVATE q3menus)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/output)