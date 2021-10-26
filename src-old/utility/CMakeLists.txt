add_library(utility STATIC)
target_sources(utility PRIVATE
  utility.c
  )
target_link_libraries(utility PRIVATE
  options
  )
