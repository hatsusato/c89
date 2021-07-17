add_library(pool STATIC)
target_sources(pool PRIVATE
  pool.c
  str.c
  str_type.c
  type.c
  )
target_link_libraries(pool PRIVATE
  options
  str
  util
  vec
  )
