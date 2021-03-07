add_library(src OBJECT)
target_sources(src PRIVATE
  main.c
  module.c
  pool.c
  print.c
  set.c
  sexp.c
  utility.c
  vector.c
  )
target_link_libraries(src PRIVATE
  ast
  builder
  options
  map
  scanner
  set
  )

add_subdirectory(ast)
add_subdirectory(builder)
add_subdirectory(compare)
add_subdirectory(map)
add_subdirectory(scanner)
add_subdirectory(set)
