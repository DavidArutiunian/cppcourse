cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(workshop.2)

include_directories(${SFML_INCLUDE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_subdirectory(workshop2.1)
add_subdirectory(workshop2.2)
add_subdirectory(workshop2.3)