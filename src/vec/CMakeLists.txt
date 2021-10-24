add_library(vec STATIC)
target_sources(vec PRIVATE
  array.c
  ptr.c
  type.c
  )
target_link_libraries(vec PRIVATE
  array
  options
  util
  )
