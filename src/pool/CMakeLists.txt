add_library(pool STATIC)
target_sources(pool PRIVATE
  pool.c
  type.c
  )
target_link_libraries(pool PRIVATE
  options
  util
  vec
  )
