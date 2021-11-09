add_library(generate STATIC)
target_sources(generate PRIVATE
  block.c
  function.c
  generate.c
  global.c
  instruction.c
  numbering.c
  )
target_link_libraries(generate PRIVATE
  json
  options
  printer
  util
  )
