#include "yyscan.h"

#include <stdio.h>

#include "cell/cell.h"
#include "parser.tab.h"
#include "type.h"
#include "util/util.h"

static struct pool *yyscan_pool(yyscan_t self) {
  return yyget_extra(self)->pool;
}

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
int yyscan_parse(yyscan_t self) {
  return yyparse(self);
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  UTIL_UNUSED(self);
  UTIL_UNUSED(symbol);
  return 0;
}
const struct cell *yyscan_nil(void) {
  return cell_nil();
}
const struct cell *yyscan_token(yyscan_t self, const char *token) {
  return cell_new_symbol(yyscan_pool(self), token);
}
const struct cell *yyscan_pair(yyscan_t self, const struct cell *car,
                               const struct cell *cdr) {
  return cell_new_cons(yyscan_pool(self), car, cdr);
}
