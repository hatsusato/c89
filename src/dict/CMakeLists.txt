add_library(dict STATIC)
target_sources(dict PRIVATE
  type.c
  )
target_link_libraries(dict PRIVATE
  options
  util
  )
