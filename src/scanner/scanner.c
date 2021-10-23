#include "scanner.h"

#include "cell/factory.h"
#include "type.h"
#include "util/util.h"
#include "yyscan.h"

const struct cell *scanner_parse(struct pool *any, struct set_symbol *symbols) {
  struct scanner scanner = {NULL, NULL};
  yyscan_t yyscan = yyscan_new(&scanner);
  if (yyscan) {
    scanner.factory = cell_factory_new(any, symbols);
    yyscan_parse(yyscan);
    cell_factory_delete(scanner.factory);
  }
  yyscan_delete(yyscan);
  return scanner.ast;
}
