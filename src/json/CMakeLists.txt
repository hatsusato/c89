add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  factory.c
  json.c
  printer.c
  str.c
  type.c
  unittest.c
  visitor.c
  vec.c
  )
target_link_libraries(json PRIVATE
  options
  printer
  util
  )
