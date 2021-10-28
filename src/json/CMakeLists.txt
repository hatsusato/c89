add_library(json STATIC)
target_sources(json PRIVATE
  arr.c
  obj.c
  type.c
  vec.c
  )
target_link_libraries(json PRIVATE
  options
  util
  )
