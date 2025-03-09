cmake_minimum_required (VERSION 3.10)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project(HxScript)
add_executable(HxScript src/Main.c)