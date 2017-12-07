cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(cppcourse)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (EXISTS ${CMAKE_SOURCE_DIR}/lib/sfml/)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/sfml/")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_modules)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
endif ()

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system)
find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)

if (${SFML_FOUND})
    include_directories(${SFML_INCLUDE_DIR})
endif ()

function(include_sfml executable)
    if (${SFML_FOUND})
        target_include_directories(${executable} PRIVATE ${SFML_INCLUDE_DIR})
        target_link_libraries(${executable} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
        target_compile_definitions(${executable} PRIVATE SFML_STATIC)
    endif ()
endfunction()

function(include_zlib executable)
    if (${ZLIB_FOUND})
        target_include_directories(${executable} PRIVATE ${ZLIB_INCLUDE_DIRS})
        target_link_libraries(${executable} ${ZLIB_LIBRARIES})
    endif ()
endfunction()

function(include_bzip2 executable)
    if (${BZIP2_FOUND})
        target_include_directories(${executable} PRIVATE ${BZIP2_INCLUDE_DIR})
        target_link_libraries(${executable} ${BZIP2_LIBRARIES})
    endif ()
endfunction()

function(copy_resources path)
    file(COPY ${path} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endfunction()

function(executable name sources)
    if (WIN32)
        add_executable(${name} WIN32 ${sources})
    else ()
        add_executable(${name} ${sources})
    endif ()
    target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)
endfunction()

add_subdirectory(cpp.1)
add_subdirectory(sfml.1)
add_subdirectory(sfml.2)
add_subdirectory(sfml.3)
add_subdirectory(workshop.1)
add_subdirectory(workshop.2)
add_subdirectory(workshop.3)