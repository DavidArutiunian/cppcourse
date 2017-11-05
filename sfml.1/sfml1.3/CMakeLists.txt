set(SOURCES main.cpp)

add_executable(sfml1.3 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(sfml1.3 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(sfml1.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(sfml1.3 PRIVATE SFML_STATIC)