cmake_minimum_required(VERSION 2.9)

project(oop-exercise-6)

include_directories(BEFORE
         ${PROJECT_SOURCE_DIR}/include  
)

add_executable(test_01 src/test_01.cpp)
add_executable(test_02 src/test_02.cpp)
add_executable(test_03 src/test_03.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
