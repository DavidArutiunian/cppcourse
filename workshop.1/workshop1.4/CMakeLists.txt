set(SOURCES main.cpp main.hpp resources)

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(workshop1.4 ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(workshop1.4 PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(workshop1.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(workshop1.4 PRIVATE SFML_STATIC)