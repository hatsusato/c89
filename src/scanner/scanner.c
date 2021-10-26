#include "scanner.h"

#include "cell/factory.h"
#include "set/set.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

static void scanner_init(struct scanner *self, struct pool *pool,
                         struct set *symbols) {
  self->factory = cell_factory_new(pool, symbols);
  self->ast = NULL;
  self->typedefs = set_new();
}
static void scanner_finish(struct scanner *self) {
  set_delete(self->typedefs);
  cell_factory_delete(self->factory);
}

const struct cell *scanner_parse(struct pool *pool, struct set *symbols) {
  struct scanner scanner = {NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner_init(&scanner, pool, symbols);
    yyscan_parse(yyscan);
    scanner_finish(&scanner);
  }
  yyscan_delete(yyscan);
  return scanner.ast;
}
