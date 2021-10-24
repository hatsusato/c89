add_library(str STATIC)
target_sources(str PRIVATE
  view_type.c
  )
target_link_libraries(str PRIVATE
  options
  util
  )
