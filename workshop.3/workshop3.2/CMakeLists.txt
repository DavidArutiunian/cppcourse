set(SOURCES main.cpp Ball.cpp Random.cpp consts.h Ball.h main.h Random.h resources Overlay.cpp Overlay.h)

set(EXECUTABLE_NAME workshop3.2)

copy_resources(resources)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})
include_bzip2(${EXECUTABLE_NAME})
include_zlib(${EXECUTABLE_NAME})