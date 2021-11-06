add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  factory.c
  int.c
  json.c
  map.c
  map_type.c
  new.c
  null.c
  obj.c
  pair.c
  print.c
  str.c
  tag.c
  type.c
  unittest.c
  util.c
  vec.c
  visitor.c
  )
target_link_libraries(json PRIVATE
  options
  printer
  util
  )
