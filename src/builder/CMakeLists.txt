add_library(builder STATIC)
target_sources(builder PRIVATE
  builder.c
  declaration.c
  expression.c
  statement.c
  )
target_link_libraries(builder PRIVATE
  ir
  json
  options
  util
  )
