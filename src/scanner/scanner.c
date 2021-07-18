#include "scanner.h"

#include "pool/str.h"
#include "pool/str_type.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

static void scanner_init(struct scanner *self, struct pool *pool) {
  self->pool = pool;
  self->table = util_malloc(sizeof(struct pool_str), 1);
  pool_str_init(self->table, pool);
  self->ast = NULL;
}
static void scanner_finish(struct scanner *self) {
  pool_str_finish(self->table);
  util_free(self->table);
}

const struct cell *scanner_parse(struct pool *pool) {
  struct scanner scanner = {NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner_init(&scanner, pool);
    yyscan_parse(yyscan);
    scanner_finish(&scanner);
  }
  yyscan_delete(yyscan);
  return scanner.ast;
}
