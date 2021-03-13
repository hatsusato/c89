add_library(map STATIC)
target_sources(map PRIVATE
  map.c
  )
target_link_libraries(map PRIVATE
  compare
  options
  set
  utility
  )
