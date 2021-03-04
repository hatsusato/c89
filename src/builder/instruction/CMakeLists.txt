add_library(instruction STATIC)
target_sources(instruction PRIVATE
  new.c
  print.c
  struct.c
  )
target_link_libraries(instruction PRIVATE
  include
  )
