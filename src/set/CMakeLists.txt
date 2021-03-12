add_library(set STATIC)
target_sources(set PRIVATE
  set.c
  sort.c
  )
target_link_libraries(set PRIVATE
  options
  compare
  vector
  utility
  )
