#include "parse.h"

#include "scanner.h"
#include "yyscan.h"

struct json *scanner_parse(struct json_factory *factory, struct set *symbols) {
  YYSCAN_EXTRA scanner = scanner_new(factory, symbols);
  yyscan_t yyscan = yyscan_new(scanner);
  struct json *top;
  if (yyscan) {
    yyscan_parse(yyscan);
  }
  yyscan_delete(yyscan);
  top = scanner_get_top(scanner);
  yyscan_delete(scanner);
  return top;
}
