#include "scanner.h"

#include "json/json.h"
#include "set/set.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

static void scanner_init(YYSCAN_EXTRA self, struct json_factory *factory,
                         struct pool *pool, struct set *symbols) {
  UTIL_UNUSED(pool);
  self->typedefs = set_new();
  self->symbols = symbols;
  self->jfactory = factory;
  self->top = json_null();
}
static void scanner_finish(YYSCAN_EXTRA self) {
  set_delete(self->typedefs);
}

struct json *scanner_parse(struct json_factory *factory, struct pool *pool,
                           struct set *symbols) {
  struct scanner scanner = {NULL, NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner_init(&scanner, factory, pool, symbols);
    yyscan_parse(yyscan);
    scanner_finish(&scanner);
  }
  yyscan_delete(yyscan);
  return scanner.top;
}
