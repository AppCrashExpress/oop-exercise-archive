# CMakeList.txt : CMake project for Vector, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 2.8)

project(oop_exercise_1)

# Add source to this project's executable.
#add_library (Vector "Vector3D.h" "Vector.cpp")
#add_executable (Menu "Menu.cpp")

add_executable (oop_exercise_1 "Vector3D.h" "Vector.cpp" "Menu.cpp")


# TODO: Add tests and install targets if needed.
