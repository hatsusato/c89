add_library(instruction STATIC)
target_sources(instruction PRIVATE
  print.c
  struct.c
  )
target_link_libraries(instruction PRIVATE
  options
  )
