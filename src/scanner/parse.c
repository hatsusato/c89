#include "parse.h"

#include "scanner.h"
#include "type.h"
#include "util/type.h"
#include "yyscan.h"

struct json *scanner_parse(struct json_factory *factory, struct set *symbols) {
  YYSCAN_EXTRA scanner = scanner_new(factory, symbols);
  yyscan_t yyscan = yyscan_new(scanner);
  struct json *top;
  if (yyscan) {
    yyscan_parse(yyscan);
  }
  yyscan_delete(yyscan);
  top = scanner->top;
  yyscan_delete(scanner);
  return top;
}
