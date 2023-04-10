cmake_minimum_required(VERSION 3.24)
project(Lab03)

set(CMAKE_CXX_STANDARD 17)
add_executable(Lab4 main.cpp)
target_link_libraries(Lab4 -lglew32 -lopengl32 -lfreeglut)
