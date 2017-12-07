set(SOURCES main.cpp main.h resources Ball.cpp Ball.h consts.h)

set(EXECUTABLE_NAME workshop3.1)

copy_resources(resources)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})
include_zlib(${EXECUTABLE_NAME})
include_bzip2(${EXECUTABLE_NAME})