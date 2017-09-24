set(SOURCES main.cpp)

add_executable(sfml.1.03 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml.1.03 PUBLIC cxx_std_17)
target_compile_definitions(sfml.1.03 PRIVATE SFML_STATIC)

target_include_directories(sfml.1.03 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml.1.03 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})