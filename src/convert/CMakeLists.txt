add_library(convert STATIC)
target_sources(convert PRIVATE
  alloc.c
  convert.c
  declaration.c
  expression.c
  function.c
  immediate.c
  module.c
  statement.c
  table.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
