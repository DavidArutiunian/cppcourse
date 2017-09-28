set(SOURCES main.cpp)

add_executable(sfml.3.04 ${SOURCES})

target_include_directories(sfml.3.04 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml.3.04 PUBLIC cxx_std_17)
target_compile_definitions(sfml.3.04 PRIVATE SFML_STATIC)

target_link_libraries(sfml.3.04 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})