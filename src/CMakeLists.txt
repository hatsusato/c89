add_executable(main)
target_sources(main PRIVATE
  main.c
  print.c
  )
target_link_libraries(main PRIVATE
  ast
  builder
  ir
  options
  printer
  map
  scanner
  set
  sexp
  utility
  )
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  SUFFIX .out
  )

add_subdirectory(ast)
add_subdirectory(builder)
add_subdirectory(ir)
add_subdirectory(map)
add_subdirectory(printer)
add_subdirectory(scanner)
add_subdirectory(set)
add_subdirectory(sexp)
add_subdirectory(utility)
add_subdirectory(vector)
