add_library(json STATIC)
target_sources(json PRIVATE
  array.c
  type.c
  )
target_link_libraries(json PRIVATE
  options
  util
  )
