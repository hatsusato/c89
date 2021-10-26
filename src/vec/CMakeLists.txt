add_library(vec STATIC)
target_sources(vec PRIVATE
  type.c
  vec.c
  )
target_link_libraries(vec PRIVATE
  array
  options
  util
  )
