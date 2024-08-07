add_executable(rolled unroll.cpp)

add_executable(unrolled unroll.cpp)
target_compile_definitions(unrolled PUBLIC UNROLL)

