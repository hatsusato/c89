add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  int.c
  json.c
  map.c
  map_type.c
  new.c
  obj.c
  pair.c
  print.c
  set.c
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
