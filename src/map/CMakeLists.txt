add_library(map STATIC)
target_sources(map PRIVATE
  map.c
  pair.c
  )
target_link_libraries(map PRIVATE
  options
  set
  utility
  )
