add_library(scanner STATIC)
target_sources(scanner PRIVATE
  register.c
  scanner.c
  yyscan.c
  )
target_link_libraries(scanner PRIVATE
  options
  parser
  )

add_subdirectory(parser)
