add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  declaration.c
  expression.c
  immediate.c
  statement.c
  type.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
