#include "parse.h"

#include "scanner.h"
#include "type.h"
#include "util/type.h"
#include "yyscan.h"

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
