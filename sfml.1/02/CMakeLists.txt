set(SOURCES main.cpp)

add_executable(sfml.1.02 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml.1.02 PUBLIC cxx_std_17)
target_compile_definitions(sfml.1.02 PRIVATE SFML_STATIC)

target_include_directories(sfml.1.02 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml.1.02 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})