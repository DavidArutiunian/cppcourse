set(SOURCES main.cpp main.hpp Ball.cpp Ball.hpp)

add_executable(workshop2.2 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop2.2 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop2.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop2.2 PRIVATE SFML_STATIC)