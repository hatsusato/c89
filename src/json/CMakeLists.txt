add_library(json STATIC)
target_sources(json PRIVATE
  factory.c
  json.c
  type.c
  vec.c
  )
target_link_libraries(json PRIVATE
  options
  util
  )
