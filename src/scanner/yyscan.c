#include "yyscan.h"

#include <stdio.h>

#include "util/util.h"

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  fprintf(stderr, "%s\n", msg);
}
int yyscan_is_typedef(yyscan_t yyscanner, const char *symbol) {
  UTIL_UNUSED(yyscanner);
  UTIL_UNUSED(symbol);
  return 0;
}
