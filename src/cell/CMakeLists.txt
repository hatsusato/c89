add_library(cell STATIC)
target_sources(cell PRIVATE
  cell.c
  factory.c
  print.c
  type.c
  )
target_link_libraries(cell PRIVATE
  options
  pool
  printer
  util
  )
