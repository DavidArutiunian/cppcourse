set(SOURCES main.cpp main.hpp Ball.cpp Ball.hpp Random.cpp Random.hpp)

set(EXECUTABLE_NAME workshop2.8)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})