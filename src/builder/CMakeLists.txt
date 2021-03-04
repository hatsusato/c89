add_library(builder STATIC)
target_sources(builder PRIVATE
  block.c
  builder.c
  constant.c
  declaration.c
  definition.c
  expression.c
  function.c
  global.c
  lexical.c
  statement.c
  table.c
  type.c
  value.c
  )
target_link_libraries(builder PRIVATE
  options
  instruction
  statement
  type
  )

add_subdirectory(instruction)
add_subdirectory(statement)
add_subdirectory(type)
