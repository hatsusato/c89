add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  immediate.c
  return.c
  switch.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
