add_library(builder STATIC)
target_sources(builder PRIVATE
  convert.c
  declaration.c
  expression.c
  immediate.c
  statement.c
  )
target_link_libraries(builder PRIVATE
  ir
  json
  options
  util
  )
