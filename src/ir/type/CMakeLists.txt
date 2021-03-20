add_library(ir_type STATIC)
target_sources(ir_type PRIVATE
  print.c
  )
target_link_libraries(ir_type PRIVATE
  options
  )
