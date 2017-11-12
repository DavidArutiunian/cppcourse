set(SOURCES main.cpp main.h resources Ball.cpp Ball.h)
set(EXECUTABLE_NAME workshop3.1)

copy_resources(resources)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

include_sfml(${EXECUTABLE_NAME})
include_zlib(${EXECUTABLE_NAME})
include_bzip2(${EXECUTABLE_NAME})

target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE SFML_STATIC)