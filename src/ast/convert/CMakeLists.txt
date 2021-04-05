add_library(convert STATIC)
target_sources(convert PRIVATE
  convert.c
  definition.c
  )
target_link_libraries(convert PRIVATE
  options
  sexp
  )
