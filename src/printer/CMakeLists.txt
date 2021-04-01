add_library(printer STATIC)
target_sources(printer PRIVATE
  printer.c
  )
target_link_libraries(printer PRIVATE
  options
  )
