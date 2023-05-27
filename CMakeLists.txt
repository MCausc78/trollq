cmake_minimum_required(VERSION 3.22)
project(trollq CXX)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB_RECURSE SOURCES "src/**.cpp")

include_directories("include")
add_executable("trollq" ${SOURCES})
