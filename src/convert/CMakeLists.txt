add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  declaration.c
  expression.c
  function.c
  immediate.c
  statement.c
  table.c
  type.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
