add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  definition.c
  statement.c
  )
target_link_libraries(convert PRIVATE
  options
  sexp
  )
