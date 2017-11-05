cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(cppcourse)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

if (${SFML_FOUND})
    include_directories(${SFML_INCLUDE_DIR})
endif ()

add_subdirectory(cpp.1)
add_subdirectory(sfml.1)
add_subdirectory(sfml.2)
add_subdirectory(sfml.3)
add_subdirectory(workshop.1)
add_subdirectory(workshop.2)