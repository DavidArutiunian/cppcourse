set(SOURCES main.cpp)

add_executable(02 ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(02 PUBLIC cxx_std_17)
target_compile_definitions(02 PRIVATE SFML_STATIC)

target_include_directories(02 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(02 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})