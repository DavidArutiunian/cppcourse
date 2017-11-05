set(SOURCES main.cpp)

add_executable(sfml2.2 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml2.2 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml2.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml2.2 PRIVATE SFML_STATIC)