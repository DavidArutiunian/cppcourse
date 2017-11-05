set(SOURCES main.cpp)

add_executable(sfml2.1 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml2.1 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml2.1 PRIVATE SFML_STATIC)