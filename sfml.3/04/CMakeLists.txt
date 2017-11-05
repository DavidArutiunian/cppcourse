set(SOURCES main.cpp)

add_executable(sfml.3.04 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml.3.04 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml.3.04 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml.3.04 PRIVATE SFML_STATIC)