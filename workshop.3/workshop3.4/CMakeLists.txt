set(SOURCES main.cpp EventLoop.cpp EventLoop.h consts.h Ship.cpp Ship.h resources)

set(EXECUTABLE_NAME workshop3.4)

copy_resources(resources)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

include_sfml(${EXECUTABLE_NAME})
include_bzip2(${EXECUTABLE_NAME})
include_zlib(${EXECUTABLE_NAME})

target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)