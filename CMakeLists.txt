cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(FileFinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  main
  main.cpp
)