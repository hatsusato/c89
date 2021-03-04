add_library(set STATIC)
target_sources(set PRIVATE
  sort.c
  )
target_link_libraries(set PRIVATE
  options
  )
