set(SOURCES main.cpp main.hpp)

set(EXECUTABLE_NAME sfml3.1)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})