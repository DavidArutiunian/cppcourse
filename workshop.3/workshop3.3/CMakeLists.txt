set(SOURCES main.cpp Line.cpp Line.h EventLoop.cpp EventLoop.h consts.h)

set(EXECUTABLE_NAME workshop3.3)

add_executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})
include_bzip2(${EXECUTABLE_NAME})
include_zlib(${EXECUTABLE_NAME})

target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)