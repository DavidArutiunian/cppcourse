cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cppcourse)

include_directories(${SFML_INCLUDE_DIR})

add_subdirectory(cpp1.1)
# add_subdirectory(cpp1.2) // Special error
add_subdirectory(cpp1.3)
add_subdirectory(cpp1.4)
add_subdirectory(sfml)
add_subdirectory(sfml1.1)
add_subdirectory(sfml1.2)
add_subdirectory(sfml1.3)