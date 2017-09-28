set(SOURCES main.cpp)

add_executable(sfml.3.03 ${SOURCES})

target_include_directories(sfml.3.03 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml.3.03 PUBLIC cxx_std_17)
target_compile_definitions(sfml.3.03 PRIVATE SFML_STATIC)

target_link_libraries(sfml.3.03 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})