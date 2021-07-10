find_package(FLEX 2.6)

FLEX_TARGET(lexer
  src/lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
  )

add_library(scanner STATIC)
target_sources(scanner PRIVATE
  ${FLEX_lexer_OUTPUTS}
  )
target_link_libraries(scanner PRIVATE
  options
  )
