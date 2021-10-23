#include "yyscan.h"

#include <assert.h>
#include <stdio.h>

#include "cell/cell.h"
#include "cell/factory.h"
#include "parser.tab.h"
#include "pool/str.h"
#include "str/view.h"
#include "str/view_type.h"
#include "type.h"
#include "util/util.h"

static struct cell_factory *yyscan_factory(yyscan_t self) {
  return yyget_extra(self)->factory;
}
static const char *yyscan_canonical_cstr(yyscan_t self, const char *str) {
  struct pool_str *table = yyget_extra(self)->table;
  return pool_str_insert(table, str);
}

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  fprintf(stderr, "%s\n", msg);
}
yyscan_t yyscan_new(struct scanner *scanner) {
  yyscan_t self;
  if (yylex_init(&self) == 0) {
    yyset_extra(scanner, self);
    return self;
  }
  return NULL;
}
void yyscan_delete(yyscan_t self) {
  if (self) {
    yylex_destroy(self);
  }
}
void yyscan_parse(yyscan_t self) {
  if (yyparse(self)) {
    yyscan_set_ast(self, NULL);
  }
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  UTIL_UNUSED(self);
  UTIL_UNUSED(symbol);
  return 0;
}
void yyscan_set_ast(yyscan_t self, const struct cell *ast) {
  yyget_extra(self)->ast = ast;
}
const struct cell *yyscan_nil(void) {
  return cell_nil();
}
const struct cell *yyscan_symbol(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return cell_factory_symbol(yyscan_factory(self), text);
}
const struct cell *yyscan_token(yyscan_t self, const char *token) {
  const char *str = yyscan_canonical_cstr(self, token);
  return cell_factory_symbol(yyscan_factory(self), str);
}
const struct cell *yyscan_pair(yyscan_t self, const struct cell *car,
                               const struct cell *cdr) {
  return cell_factory_cons(yyscan_factory(self), car, cdr);
}
const struct cell *yyscan_push(yyscan_t self, const struct cell *xs,
                               const struct cell *x) {
  return cell_factory_push(yyscan_factory(self), xs, x);
}
