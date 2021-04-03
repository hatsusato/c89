add_library(sexp STATIC)
target_sources(sexp PRIVATE
  sexp.c
  )
target_link_libraries(sexp PRIVATE
  ast
  options
  printer
  )
