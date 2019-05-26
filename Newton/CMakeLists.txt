cmake_minimum_required(VERSION 3.0.0)
project(newt VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(newtt newt_type.cpp)
add_executable(newts newt_sqrt.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
