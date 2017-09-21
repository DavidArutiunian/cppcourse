set(SOURCES main.cpp)

add_executable(00 ${SOURCES})

target_compile_features(00 PUBLIC cxx_std_17)