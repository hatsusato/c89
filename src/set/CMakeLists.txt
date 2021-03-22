add_library(set STATIC)
target_sources(set PRIVATE
  set.c
  )
target_link_libraries(set PRIVATE
  options
  vector
  utility
  )
