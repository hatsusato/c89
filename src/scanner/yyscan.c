#include "yyscan.h"

#include <stdio.h>

#include "parser.tab.h"
#include "util/util.h"

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  fprintf(stderr, "%s\n", msg);
}
yyscan_t yyscan_new(struct scanner *scanner) {
  yyscan_t self;
  if (yylex_init(&self)) {
    return NULL;
  }
  yyset_extra(scanner, self);
  return self;
}
void yyscan_delete(yyscan_t self) {
  yylex_destroy(self);
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  UTIL_UNUSED(self);
  UTIL_UNUSED(symbol);
  return 0;
}
