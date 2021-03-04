add_library(type STATIC)
target_sources(type PRIVATE
  print.c
  spec.c
  )
target_link_libraries(type PRIVATE
  options
  )
