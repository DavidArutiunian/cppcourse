set(SOURCES main.cpp main.h resources Ball.cpp Ball.h)
set(EXECUTABLE_NAME workshop3.1)

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(${EXECUTABLE_NAME} ${SOURCES})

if (${SFML_FOUND})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE SFML_STATIC)