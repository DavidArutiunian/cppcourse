cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(sfml1.3)

set(SOURCES main.cpp)

add_executable(sfml1.3 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml1.3 PUBLIC cxx_std_17)
target_compile_definitions(sfml1.3 PRIVATE SFML_STATIC)

target_include_directories(sfml1.3 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml1.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})