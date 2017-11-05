set(SOURCES main.cpp main.hpp Ball.cpp Ball.hpp Random.cpp Random.hpp)

add_executable(workshop2.7 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop2.7 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop2.7 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop2.7 PRIVATE SFML_STATIC)