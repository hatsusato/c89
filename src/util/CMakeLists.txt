add_library(util STATIC)
target_sources(util PRIVATE
  buffer.c
  type.c
  util.c
  )
target_link_libraries(util PRIVATE
  options
  )
