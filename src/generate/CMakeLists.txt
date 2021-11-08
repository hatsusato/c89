add_library(generate STATIC)
target_sources(generate PRIVATE
  block.c
  generate.c
  instruction.c
  numbering.c
  )
target_link_libraries(generate PRIVATE
  json
  options
  printer
  util
  )
