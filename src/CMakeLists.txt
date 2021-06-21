add_executable(main)
target_sources(main PRIVATE
  main.c
  )
target_link_libraries(main PRIVATE
  options
  vector
  )
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  SUFFIX .out
  )

add_subdirectory(vector)
