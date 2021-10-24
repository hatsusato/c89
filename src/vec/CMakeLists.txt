add_library(vec STATIC)
target_sources(vec PRIVATE
  array.c
  type.c
  vec.c
  )
target_link_libraries(vec PRIVATE
  options
  util
  )
