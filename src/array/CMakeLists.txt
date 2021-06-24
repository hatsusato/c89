add_library(array STATIC)
target_sources(array PRIVATE
  array.c
  )
target_link_libraries(array PRIVATE
  options
  util
  )
