#include "parse.h"

#include "scanner.h"
#include "yyscan.h"

struct json *scanner_parse(struct json_set *symbols) {
  struct json *top;
  YYSCAN_EXTRA scanner = scanner_new(symbols);
  yyscan_parse(scanner);
  top = scanner_get_top(scanner);
  scanner_del(scanner);
  return top;
}
