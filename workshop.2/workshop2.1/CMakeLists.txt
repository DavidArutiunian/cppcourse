set(SOURCES main.cpp main.hpp)

add_executable(workshop2.1 ${SOURCES})

include_directories(${SFML_INCLUDE_DIR})

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(workshop2.1 PUBLIC cxx_std_17)
target_compile_definitions(workshop2.1 PRIVATE SFML_STATIC)

target_include_directories(workshop2.1 PRIVATE ${SFML_INCLUDE_DIR})

target_link_libraries(workshop2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})