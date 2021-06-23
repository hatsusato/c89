add_library(str STATIC)
target_sources(str PRIVATE
  str.c
  )
target_link_libraries(str PRIVATE
  options
  )
