add_library(cell STATIC)
target_sources(cell PRIVATE
  cell.c
  factory.c
  print.c
  tag.c
  type.c
  visitor.c
  )
target_link_libraries(cell PRIVATE
  options
  pool
  printer
  util
  )
