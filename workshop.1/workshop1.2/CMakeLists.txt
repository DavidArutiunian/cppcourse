set(SOURCES main.cpp main.hpp)

set(EXECUTABLE_NAME workshop1.2)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})