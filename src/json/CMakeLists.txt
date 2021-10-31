add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  factory.c
  json.c
  obj.c
  pair.c
  printer.c
  str.c
  type.c
  unittest.c
  vec.c
  visitor.c
  )
target_link_libraries(json PRIVATE
  options
  printer
  util
  )
