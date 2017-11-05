set(SOURCES main.cpp main.hpp)

add_executable(workshop1.2 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop1.2 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop1.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop1.2 PRIVATE SFML_STATIC)