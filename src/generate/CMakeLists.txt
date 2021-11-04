add_library(generate STATIC)
target_sources(generate PRIVATE
  generate.c
  )
target_link_libraries(generate PRIVATE
  json
  options
  util
  )
