add_executable(main)
target_sources(main PRIVATE
  main.c
  )
target_link_libraries(main PRIVATE
  options
  $<$<CONFIG:Debug>:unittest>
  )
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  SUFFIX .out
  )

add_library(unittest STATIC)
target_sources(unittest PRIVATE
  vec/unittest.c
  )
target_link_libraries(unittest PRIVATE
  options
  utility
  vec
  )

add_subdirectory(utility)
add_subdirectory(vec)
