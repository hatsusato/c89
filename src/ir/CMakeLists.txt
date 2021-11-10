add_library(ir STATIC)
target_sources(ir PRIVATE
  global.c
  module.c
  value.c
  )
target_link_libraries(ir PRIVATE
  json
  options
  util
  )
