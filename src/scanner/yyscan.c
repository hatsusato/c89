#include "yyscan.h"

#include "util/util.h"

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  UTIL_UNUSED(msg);
}
int yyscan_is_typedef(yyscan_t yyscanner, const char *symbol) {
  UTIL_UNUSED(yyscanner);
  UTIL_UNUSED(symbol);
  return 0;
}
