#include "parse.h"

#include "scanner.h"
#include "yyscan.h"

struct json *scanner_parse(struct json_factory *factory, struct set *symbols) {
  struct json *top;
  YYSCAN_EXTRA scanner = scanner_new(factory, symbols);
  yyscan_parse(scanner);
  top = scanner_get_top(scanner);
  scanner_delete(scanner);
  return top;
}
