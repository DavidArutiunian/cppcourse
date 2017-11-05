set(SOURCES main.cpp main.hpp img)

add_executable(workshop1.3 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop1.3 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop1.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop1.3 PRIVATE SFML_STATIC)