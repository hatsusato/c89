#include "scanner.h"

#include "cell/factory.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

static void scanner_init(struct scanner *self, struct pool *pool) {
  self->pool = pool;
  self->ast = NULL;
}

const struct cell *scanner_parse(struct pool *pool, struct pool_any *any,
                                 struct set_symbol *symbols) {
  struct scanner scanner = {NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner.factory = cell_factory_new(any, symbols);
    scanner_init(&scanner, pool);
    yyscan_parse(yyscan);
    cell_factory_delete(scanner.factory);
  }
  yyscan_delete(yyscan);
  return scanner.ast;
}
