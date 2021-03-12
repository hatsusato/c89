add_library(compare OBJECT)
target_sources(compare PRIVATE
  compare.c
  )
target_link_libraries(compare PRIVATE
  options
  utility
  )
