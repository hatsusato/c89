#include "scanner.h"

#include "pool/str.h"
#include "pool/type.h"
#include "type.h"
#include "util/box.h"
#include "yyscan.h"

static void scanner_init(struct scanner *self, struct pool *pool) {
  struct box *box = box_new(sizeof(struct pool_str), 1);
  self->pool = pool;
  self->table = box_get(box);
  pool_str_init(self->table, pool);
  self->ast = NULL;
}
static void scanner_finish(struct scanner *self) {
  pool_str_finish(self->table);
  box_release(self->table);
}

const struct cell *scanner_parse(struct pool *pool) {
  struct scanner scanner = {NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner_init(&scanner, pool);
    if (yyscan_parse(yyscan)) {
      scanner.ast = NULL;
    }
    scanner_finish(&scanner);
  }
  return scanner.ast;
}
