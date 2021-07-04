add_library(util STATIC)
target_sources(util PRIVATE
  box.c
  buffer.c
  slice.c
  type.c
  util.c
  )
target_link_libraries(util PRIVATE
  options
  )
