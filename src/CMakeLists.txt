add_executable(rolled unroll.cpp)

add_executable(unrolled unroll.cpp)
target_compile_definitions(unrolled PUBLIC UNROLL)

add_executable(cunrolled unroll.cpp)
target_compile_definitions(cunrolled PUBLIC COMP_UNROLL)

add_executable(cmunrolled unroll.cpp)
target_compile_definitions(cmunrolled PUBLIC COMP_MUNROLL)
