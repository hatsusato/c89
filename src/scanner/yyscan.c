#include "yyscan.h"

#include "cell/cell.h"
#include "cell/factory.h"
#include "json/factory.h"
#include "json/json.h"
#include "parser.tab.h"
#include "set/set.h"
#include "type.h"
#include "typedef.h"
#include "util/util.h"

static struct cell_factory *yyscan_factory(yyscan_t self) {
  return yyget_extra(self)->factory;
}

void yyerror(yyscan_t yyscanner, const char *msg) {
  UTIL_UNUSED(yyscanner);
  util_error("%s", msg);
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
    yyscan_set_ast(self, cell_nil());
  }
}
int yyscan_is_typedef(yyscan_t self, const char *symbol) {
  const char *found = set_find(yyget_extra(self)->typedefs, symbol);
  return found ? 1 : 0;
}
void yyscan_register_typedef(yyscan_t self, const struct cell *decl) {
  if (typedef_contains(decl)) {
    typedef_register(decl, yyget_extra(self)->typedefs);
  }
}
void yyscan_set_ast(yyscan_t self, const struct cell *ast) {
  yyget_extra(self)->ast = ast;
}
const struct cell *yyscan_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return yyscan_symbol(self, text);
}
const struct cell *yyscan_symbol(yyscan_t self, const char *symbol) {
  return cell_factory_symbol(yyscan_factory(self), symbol);
}
const struct cell *yyscan_push(yyscan_t self, const struct cell *xs,
                               const struct cell *x) {
  return cell_factory_push(yyscan_factory(self), xs, x);
}
const struct cell *yyscan_list(yyscan_t self, int count, ...) {
  const struct cell *list;
  va_list args;
  va_start(args, count);
  list = cell_factory_list(yyscan_factory(self), count, args);
  va_end(args);
  return list;
}

struct json *yyscan_json_null(void) {
  return json_null();
}
struct json *yyscan_json_token(yyscan_t self) {
  const char *text = yyget_text(self);
  assert(text[yyget_leng(self)] == 0);
  return yyscan_json_symbol(self, text);
}
struct json *yyscan_json_symbol(yyscan_t self, const char *symbol) {
  symbol = set_insert(yyget_extra(self)->symbols, symbol);
  return json_factory_str(yyget_extra(self)->jfactory, symbol);
}
struct json *yyscan_json_arr(yyscan_t self) {
  return json_factory_arr(yyget_extra(self)->jfactory);
}
struct json *yyscan_json_push(struct json *json, struct json *val) {
  json_arr_push(json, val);
  return json;
}
struct json *yyscan_json_obj(yyscan_t self) {
  return json_factory_obj(yyget_extra(self)->jfactory);
}
void yyscan_json_insert(struct json *json, const char *key, struct json *val) {
  json_obj_set(json, key, val);
}
