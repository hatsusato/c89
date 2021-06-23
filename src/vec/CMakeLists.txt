add_library(vec STATIC)
target_sources(vec PRIVATE
  vec.c
  vec_ptr.c
  )
target_link_libraries(vec PRIVATE
  options
  util
  )
