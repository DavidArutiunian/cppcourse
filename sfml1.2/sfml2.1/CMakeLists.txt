set(SOURCES main.cpp)

add_executable(sfml2.1 ${SOURCES})

include_directories(${SFML_INCLUDE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(sfml2.1 PUBLIC cxx_std_17)
target_compile_definitions(sfml2.1 PRIVATE SFML_STATIC)

target_include_directories(sfml2.1 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(sfml2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})