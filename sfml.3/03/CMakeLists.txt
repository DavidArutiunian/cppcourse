set(SOURCES main.cpp)

add_executable(sfml.3.03 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml.3.03 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml.3.03 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml.3.03 PRIVATE SFML_STATIC)