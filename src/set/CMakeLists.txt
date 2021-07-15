add_library(set STATIC)
target_sources(set PRIVATE
  type.c
  )
target_link_libraries(set PRIVATE
  options
  util
  vec
  )
