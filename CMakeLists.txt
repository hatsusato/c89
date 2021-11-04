cmake_minimum_required(VERSION 3.10)
project(c89 C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BuildType)
include(CompileCommands)
include(DevelopFlag)

add_custom_target(develop)
develop_flag_option()
if(DEVELOP_FLAG)
  set_build_types(Debug Release)
  export_compile_commands(develop)
else()
  set_build_types(Release Debug)
endif()

add_library(options INTERFACE)
target_compile_options(options INTERFACE
  -ansi
  -pedantic
  -Wall
  -Wextra
  -Werror
  $<$<CONFIG:Debug>:-O0>
  )
target_include_directories(options INTERFACE
  src
  )

add_subdirectory(src)
