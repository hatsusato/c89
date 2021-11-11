add_executable(main)
target_sources(main PRIVATE
  main.c
  )
target_link_libraries(main PRIVATE
  builder
  generate
  json
  options
  scanner
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
  json/unittest.c
  )
target_link_libraries(unittest PRIVATE
  json
  options
  util
  )

add_subdirectory(builder)
add_subdirectory(generate)
add_subdirectory(ir)
add_subdirectory(json)
add_subdirectory(printer)
add_subdirectory(scanner)
add_subdirectory(util)
