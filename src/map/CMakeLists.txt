add_library(map STATIC)
target_sources(map PRIVATE
  pair.c
  )
target_link_libraries(map PRIVATE
  include
  )
