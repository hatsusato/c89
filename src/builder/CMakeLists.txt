add_library(builder STATIC)
target_sources(builder PRIVATE
  builder.c
  declaration.c
  definition.c
  expression.c
  lexical.c
  statement.c
  table.c
  )
target_link_libraries(builder PRIVATE
  map
  options
  statement
  )

add_subdirectory(statement)
