add_library(statement STATIC)
target_sources(statement PRIVATE
  common.c
  iteration.c
  jump.c
  labeled.c
  selection.c
  )
target_link_libraries(statement PRIVATE
  options
  )
