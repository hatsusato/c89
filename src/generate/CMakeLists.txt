add_library(generate STATIC)
target_sources(generate PRIVATE
  generate.c
  instruction.c
  )
target_link_libraries(generate PRIVATE
  json
  options
  printer
  util
  )
