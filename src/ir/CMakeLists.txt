add_library(ir STATIC)
target_sources(ir PRIVATE
  block.c
  constant.c
  function.c
  global.c
  module.c
  type.c
  value.c
  )
target_link_libraries(ir PRIVATE
  builder
  instruction
  options
  ir_type
  )

add_subdirectory(instruction)
add_subdirectory(type)
