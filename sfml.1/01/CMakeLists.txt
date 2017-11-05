set(SOURCES main.cpp)

add_executable(sfml.1.01 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml.1.01 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml.1.01 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml.1.01 PRIVATE SFML_STATIC)