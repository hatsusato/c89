#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "module.h"
#include "util/symbol.h"

static void convert_compound_statement(struct json *module, struct json *json) {
  ir_module_push_scope(module);
  convert_declaration(module, json);
  convert_statement(module, json);
  ir_module_pop_scope(module);
}
static void convert_expression_statement(struct json *module,
                                         struct json *json) {
  convert_rvalue(module, json_get(json, SYMBOL_EXPRESSION));
}
static void convert_jump_statement(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *expr =
        convert_rvalue(module, json_get(json, SYMBOL_EXPRESSION));
    struct json *instr = convert_push_instr(module, "ret");
    json_insert(instr, "value", expr);
  }
}
static void convert_statement_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  convert_statement(module, json);
}

void convert_statement(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    convert_compound_statement(module,
                               json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_EXPRESSION_STATEMENT)) {
    convert_expression_statement(module,
                                 json_get(json, SYMBOL_EXPRESSION_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    convert_jump_statement(module, json_get(json, SYMBOL_JUMP_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_get(json, SYMBOL_STATEMENT_LIST), convert_statement_list,
                 module);
  }
}
