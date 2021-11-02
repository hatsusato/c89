add_library(json STATIC)
target_sources(json PRIVATE
  any.c
  arr.c
  factory.c
  int.c
  json.c
  map.c
  null.c
  obj.c
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
