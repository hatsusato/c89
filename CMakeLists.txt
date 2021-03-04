cmake_minimum_required(VERSION 3.10)
project(c89 C)

add_library(options INTERFACE)
target_compile_options(options INTERFACE
  -ansi
  -pedantic
  -Wall
  -Wextra
  )
target_include_directories(options INTERFACE
  include
  )

add_executable(main "")
set_target_properties(main PROPERTIES
  LINKER_LANGUAGE C
  SUFFIX .out
  )
target_link_libraries(main PRIVATE
  options
  src
  )

add_subdirectory(src)
