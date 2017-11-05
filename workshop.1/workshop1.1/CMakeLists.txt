set(SOURCES main.cpp main.hpp)

add_executable(workshop1.1 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop1.1 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop1.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop1.1 PRIVATE SFML_STATIC)