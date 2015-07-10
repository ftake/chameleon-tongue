cmake_minimum_required(VERSION 2.8)

set(IMSettings_VERSION_MAJOR 1)
set(IMSettings_VERSION_MINOR 0)

configure_file(
  "${PROJECT_SOURCE_DIR}/IMSettingsConfig.h.in"
  "${PROJECT_BINARY_DIR}/IMSettingsConfig.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

#set(CMAKE_CXX_COMPILER_ID Clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
add_compile_options(-std=c++11 -Wall)

find_package(Boost 1.54 REQUIRED COMPONENTS log program_options filesystem system)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_executable(im-settings Options.cc Environment.cc SubCommand.cc AutoSelect.cc main.cc)
target_link_libraries(im-settings ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )
