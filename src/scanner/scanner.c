#include "scanner.h"

#include "parser.tab.h"
#include "pool/str.h"
#include "pool/type.h"
#include "type.h"
#include "util/box.h"

static yyscan_t scanner_init(struct scanner *self, struct pool *pool) {
  yyscan_t yyscan;
  struct box *box;
  if (yylex_init(&yyscan)) {
    return NULL;
  }
  box = box_new(sizeof(struct pool_str), 1);
  self->pool = pool;
  self->table = box_get(box);
  pool_str_init(self->table, pool);
  self->ast = NULL;
  yyset_extra(self, yyscan);
  return yyscan;
}
static void scanner_finish(struct scanner *self) {
  pool_str_finish(self->table);
  box_release(self->table);
}

const struct cell *scanner_parse(struct pool *pool) {
  struct scanner scanner;
  yyscan_t yyscan = scanner_init(&scanner, pool);
  if (yyscan) {
    if (yyparse(yyscan)) {
      scanner.ast = NULL;
    }
    scanner_finish(&scanner);
    yylex_destroy(yyscan);
  }
  return scanner.ast;
}
