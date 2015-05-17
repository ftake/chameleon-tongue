cmake_minimum_required(VERSION 2.8)

#set(CMAKE_CXX_COMPILER_ID Clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
add_compile_options(-std=c++11 -Wall)

find_package(Boost 1.54 REQUIRED COMPONENTS program_options filesystem system)
include_directories(${Boost_INCLUDE_DIR})
add_executable(im-settings select-im.cc main.cc)
target_link_libraries(im-settings ${Boost_LIBRARIES})
