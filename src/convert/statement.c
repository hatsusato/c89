#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "json/json.h"
#include "json/map.h"
#include "type.h"
#include "util/symbol.h"

static void convert_compound_statement(struct convert *self,
                                       struct json *json) {
  convert_declaration(self, json);
  convert_statement(self, json);
}
static void convert_expression_statement(struct convert *self,
                                         struct json *json) {
  convert_rvalue(self, json_get(json, SYMBOL_EXPRESSION));
}
static void convert_jump_statement(struct convert *self, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *instr = convert_extra_new_instr("ret");
    struct json *expr = convert_rvalue(self, json_get(json, SYMBOL_EXPRESSION));
    json_insert(instr, "value", expr);
    convert_extra_push_instr(self, instr);
    json_del(instr);
  }
}
static void convert_statement_list(struct json_map *map) {
  struct convert *self = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_statement(self, json);
}

void convert_statement(struct convert *self, struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    convert_compound_statement(self, json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_EXPRESSION_STATEMENT)) {
    convert_expression_statement(self,
                                 json_get(json, SYMBOL_EXPRESSION_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    convert_jump_statement(self, json_get(json, SYMBOL_JUMP_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_get(json, SYMBOL_STATEMENT_LIST), convert_statement_list,
                 self);
  }
}
