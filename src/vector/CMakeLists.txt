add_library(vector STATIC)
target_sources(vector PRIVATE
  span.c
  vec.c
  )
target_link_libraries(vector PRIVATE
  options
  utility
  )
