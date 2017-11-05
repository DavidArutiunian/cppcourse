set(SOURCES main.cpp main.hpp)

add_executable(workshop2.1 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop2.1 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop2.1 PRIVATE SFML_STATIC)