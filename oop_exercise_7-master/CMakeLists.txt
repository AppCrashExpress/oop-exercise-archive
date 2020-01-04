cmake_minimum_required(VERSION 2.9)

project(oop_exercise_7)

include_directories(BEFORE
         ${PROJECT_SOURCE_DIR}/include  
)

add_executable(${PROJECT_NAME} src/main.cpp)
