cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(sfml1.1)

set(SOURCES main.cpp)

add_executable(sfml1.1 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml1.1 PUBLIC cxx_std_17)
target_compile_definitions(sfml1.1 PRIVATE SFML_STATIC)

target_include_directories(sfml1.1 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml1.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})