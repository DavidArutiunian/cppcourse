set(SOURCES main.cpp main.hpp resources)

copy_resources(resources)

set(EXECUTABLE_NAME workshop1.3)

executable(${EXECUTABLE_NAME} "${SOURCES}")

include_sfml(${EXECUTABLE_NAME})