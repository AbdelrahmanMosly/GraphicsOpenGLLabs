cmake_minimum_required(VERSION 3.24)
project(Lab0)

set(CMAKE_CXX_STANDARD 17)
add_executable(Lab2 main.cpp)
target_link_libraries(Lab2 -lglew32 -lopengl32 -lfreeglut)
