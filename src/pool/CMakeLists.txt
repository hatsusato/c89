add_library(pool OBJECT)
target_sources(pool PRIVATE
  pool.c
  )
target_link_libraries(pool PRIVATE
  options
  )
