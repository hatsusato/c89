add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  declaration.c
  expression.c
  immediate.c
  statement.c
  )
target_link_libraries(convert PRIVATE
  ir
  json
  options
  util
  )
