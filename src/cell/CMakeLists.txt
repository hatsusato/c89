add_library(cell STATIC)
target_sources(cell PRIVATE
  type.c
  )
target_link_libraries(cell PRIVATE
  options
  )
