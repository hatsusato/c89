cmake_minimum_required(VERSION 3.10)
project(c89 C)

add_library(include INTERFACE)
target_include_directories(include INTERFACE
  include
  )

add_executable(main "")
set_target_properties(main PROPERTIES
  LINKER_LANGUAGE C
  SUFFIX .out
  )
target_link_libraries(main PRIVATE
  include
  src
  )

add_subdirectory(src)
