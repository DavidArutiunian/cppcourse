cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(sfml1.2)

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)

set(SOURCES main.cpp)

add_executable(sfml1.2 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml1.2 PUBLIC cxx_std_17)
target_compile_definitions(sfml1.2 PRIVATE SFML_STATIC)

target_include_directories(sfml1.2 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml1.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})