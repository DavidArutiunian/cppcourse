cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(sfml.3)

include_directories(${SFML_INCLUDE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(sfml3.1)
add_subdirectory(sfml3.2)
add_subdirectory(sfml3.3)