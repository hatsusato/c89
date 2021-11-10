add_library(ir STATIC)
target_sources(ir PRIVATE
  block.c
  function.c
  instr.c
  module.c
  table.c
  value.c
  )
target_link_libraries(ir PRIVATE
  json
  options
  util
  )
