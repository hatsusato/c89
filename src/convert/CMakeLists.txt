add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  )
target_link_libraries(convert PRIVATE
  options
  util
  )
