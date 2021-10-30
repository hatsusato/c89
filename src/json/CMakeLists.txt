add_library(json STATIC)
target_sources(json PRIVATE
  factory.c
  json.c
  printer.c
  type.c
  unittest.c
  vec.c
  )
target_link_libraries(json PRIVATE
  options
  printer
  util
  )
