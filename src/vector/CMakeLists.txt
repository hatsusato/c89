add_library(vector STATIC)
target_sources(vector PRIVATE
  vector.c
  )
target_link_libraries(vector PRIVATE
  options
  )
