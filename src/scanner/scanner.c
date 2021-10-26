#include "scanner.h"

#include "cell/factory.h"
#include "set/set.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

const struct cell *scanner_parse(struct pool *pool, struct set *symbols) {
  struct scanner scanner = {NULL, NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner.factory = cell_factory_new(pool, symbols);
    scanner.typedefs = set_new();
    yyscan_parse(yyscan);
    set_delete(scanner.typedefs);
    cell_factory_delete(scanner.factory);
  }
  yyscan_delete(yyscan);
  return scanner.ast;
}
