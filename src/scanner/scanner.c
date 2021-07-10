#include "scanner.h"

#include "cell/cell.h"
#include "parser.tab.h"
#include "type.h"

const struct cell *scanner_parse(void) {
  yyscan_t yyscan;
  struct scanner scanner;
  if (yylex_init(&yyscan)) {
    return NULL;
  }
  scanner.ast = cell_nil();
  yyset_extra(&scanner, yyscan);
  if (yyparse(yyscan)) {
    scanner.ast = NULL;
  }
  yylex_destroy(yyscan);
  return scanner.ast;
}
