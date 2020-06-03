cmake_minimum_required(VERSION 3.14)

project(dss_exercise)

list(APPEND dss_exercise_src "src/main.cpp")

add_executable(dss_exercise ${dss_exercise_src})
