add_library(vector STATIC)
target_sources(vector PRIVATE
  vec.c
  vec_ptr.c
  )
target_link_libraries(vector PRIVATE
  options
  utility
  )
