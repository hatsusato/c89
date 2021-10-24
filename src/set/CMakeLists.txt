add_library(set STATIC)
target_sources(set PRIVATE
  symbol.c
  type.c
  )
target_link_libraries(set PRIVATE
  options
  util
  vec
  )
