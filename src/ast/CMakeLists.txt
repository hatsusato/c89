add_library(ast STATIC)
target_sources(ast PRIVATE
  ast.c
  convert.c
  tag.c
  )
target_link_libraries(ast PRIVATE
  options
  printer
  set
  sexp
  utility
  )
