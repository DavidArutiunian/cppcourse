cmake_minimum_required(VERSION 3.6.2 FATAL_ERROR)

project(hello)

set(SOURCES hello.cpp)

add_executable(hello ${SOURCES})