set(SOURCES main.cpp main.hpp Ball.cpp Ball.hpp)

set(EXECUTABLE_NAME workshop2.2)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})