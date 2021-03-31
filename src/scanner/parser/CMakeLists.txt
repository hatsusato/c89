find_package(FLEX 2.6)
find_package(BISON 3.0)

FLEX_TARGET(lexer
  lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
  )
BISON_TARGET(parser
  parser.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
  )
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_library(parser OBJECT)
target_sources(parser PRIVATE
  ${BISON_parser_OUTPUTS}
  ${FLEX_lexer_OUTPUTS}
  yyscan.c
  )
target_include_directories(parser PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )
target_link_libraries(parser PRIVATE
  options
  )
