add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  immediate.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
