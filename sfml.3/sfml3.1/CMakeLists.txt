set(SOURCES main.cpp main.hpp)

add_executable(sfml3.1 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml3.1 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml3.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml3.1 PRIVATE SFML_STATIC)