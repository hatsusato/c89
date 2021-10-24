add_executable(main)
target_sources(main PRIVATE
  main.c
  )
target_link_libraries(main PRIVATE
  options
  pool
  printer
  scanner
  set
  util
  $<$<CONFIG:Debug>:unittest>
  )
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  SUFFIX .out
  )

add_library(unittest STATIC)
target_sources(unittest PRIVATE
  unittest.c
  array/unittest.c
  cell/unittest.c
  pool/unittest.c
  set/unittest.c
  vec/unittest.c
  )
target_link_libraries(unittest PRIVATE
  array
  cell
  options
  pool
  set
  str
  util
  vec
  )

add_subdirectory(array)
add_subdirectory(cell)
add_subdirectory(pool)
add_subdirectory(printer)
add_subdirectory(scanner)
add_subdirectory(set)
add_subdirectory(str)
add_subdirectory(util)
add_subdirectory(vec)
