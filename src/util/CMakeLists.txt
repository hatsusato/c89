add_library(util STATIC)
target_sources(util PRIVATE
  box.c
  box_type.c
  buffer.c
  type.c
  util.c
  )
target_link_libraries(util PRIVATE
  options
  )
