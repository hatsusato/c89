find_package(FLEX 2.6)
find_package(BISON 3.0)

FLEX_TARGET(lexer
  src/lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
  )
BISON_TARGET(parser
  src/parser.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
  )
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_library(scanner STATIC)
target_sources(scanner PRIVATE
  ${BISON_parser_OUTPUTS}
  ${FLEX_lexer_OUTPUTS}
  parse.c
  scanner.c
  yyscan.c
  yyscan_t.c
  )
target_include_directories(scanner PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
target_link_libraries(scanner PRIVATE
  json
  options
  util
  )
