add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  declaration.c
  expression.c
  extra.c
  statement.c
  )
target_link_libraries(convert PRIVATE
  json
  options
  util
  )
