cmake_minimum_required(VERSION 3.21)

#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang)
project(fuzz-vec)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-fsanitize=fuzzer")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(fuzz-vec ./fuzz_vec.cc)
target_link_libraries(fuzz-vec vector)

target_compile_options(fuzz-vec
            PRIVATE -g -O1 "-fsanitize=fuzzer"
            )
add_subdirectory(vector)