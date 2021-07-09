add_library(vec STATIC)
target_sources(vec PRIVATE
  ptr.c
  type.c
  vec.c
  )
target_link_libraries(vec PRIVATE
  array
  options
  util
  )
