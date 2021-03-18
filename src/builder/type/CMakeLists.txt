add_library(builder_type STATIC)
target_sources(builder_type PRIVATE
  spec.c
  )
target_link_libraries(builder_type PRIVATE
  options
  )
