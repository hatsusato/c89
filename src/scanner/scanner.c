#include "scanner.h"

#include "cell/cell.h"
#include "parser.tab.h"
#include "type.h"

static yyscan_t scanner_init(struct scanner *self) {
  yyscan_t yyscan;
  if (yylex_init(&yyscan)) {
    return NULL;
  }
  self->ast = NULL;
  yyset_extra(self, yyscan);
  return yyscan;
}

const struct cell *scanner_parse(void) {
  struct scanner scanner;
  yyscan_t yyscan = scanner_init(&scanner);
  if (yyscan) {
    if (yyparse(yyscan)) {
      scanner.ast = NULL;
    }
    yylex_destroy(yyscan);
  }
  return scanner.ast;
}
