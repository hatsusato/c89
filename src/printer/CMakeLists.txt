add_library(printer STATIC)
target_sources(printer PRIVATE
  type.c
  printer.c
  )
target_link_libraries(printer PRIVATE
  options
  )
