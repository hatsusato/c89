add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  factory.c
  json.c
  map.c
  null.c
  obj.c
  printer.c
  str.c
  tag.c
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
