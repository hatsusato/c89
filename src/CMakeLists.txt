add_library(src OBJECT)
target_sources(src PRIVATE
  main.c
  print.c
  )
target_link_libraries(src PRIVATE
  ast
  builder
  compare
  options
  map
  scanner
  set
  sexp
  utility
  )

add_subdirectory(ast)
add_subdirectory(builder)
add_subdirectory(compare)
add_subdirectory(map)
add_subdirectory(pool)
add_subdirectory(scanner)
add_subdirectory(set)
add_subdirectory(sexp)
add_subdirectory(utility)
add_subdirectory(vector)
