add_library(cell STATIC)
target_sources(cell PRIVATE
  cell.c
  type.c
  )
target_link_libraries(cell PRIVATE
  options
  pool
  util
  )
