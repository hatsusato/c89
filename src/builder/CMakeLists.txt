add_library(builder STATIC)
target_sources(builder PRIVATE
  builder.c
  declaration.c
  definition.c
  expression.c
  ir.c
  lexical.c
  statement.c
  table.c
  )
target_link_libraries(builder PRIVATE
  map
  options
  statement
  builder_type
  )

add_subdirectory(statement)
add_subdirectory(type)
