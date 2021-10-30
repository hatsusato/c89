#include "scanner.h"

#include "json/json.h"
#include "set/set.h"
#include "type.h"
#include "util/util.h"

void scanner_init(YYSCAN_EXTRA self, struct json_factory *factory,
                  struct pool *pool, struct set *symbols) {
  UTIL_UNUSED(pool);
  self->typedefs = set_new();
  self->symbols = symbols;
  self->jfactory = factory;
  self->top = json_null();
}
void scanner_finish(YYSCAN_EXTRA self) {
  set_delete(self->typedefs);
}
YYSCAN_EXTRA scanner_new(struct json_factory *factory, struct set *symbols) {
  YYSCAN_EXTRA self = util_malloc(sizeof(struct scanner));
  self->typedefs = set_new();
  self->symbols = symbols;
  self->jfactory = factory;
  self->top = json_null();
  return self;
}
void scanner_delete(YYSCAN_EXTRA self) {
  set_delete(self->typedefs);
  util_free(self);
}
