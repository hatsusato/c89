add_library(pool STATIC)
target_sources(pool PRIVATE
  any.c
  pool.c
  type.c
  )
target_link_libraries(pool PRIVATE
  options
  util
  vec
  )
