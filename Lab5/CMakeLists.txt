cmake_minimum_required(VERSION 3.24)
project(Lab05)

set(CMAKE_CXX_STANDARD 17)
add_executable(Lab5 main.cpp)
target_link_libraries(Lab5 -lglew32 -lopengl32 -lfreeglut)
