add_library(array STATIC)
target_sources(array PRIVATE
  slice.c
  slice_type.c
  )
target_link_libraries(array PRIVATE
  options
  util
  )
