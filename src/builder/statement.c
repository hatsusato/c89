#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void builder_compound_statement(struct json *module, struct json *json) {
  ir_module_push_scope(module);
  builder_declaration(module, json);
  builder_statement(module, json);
  ir_module_pop_scope(module);
}
static void builder_expression_statement(struct json *module,
                                         struct json *json) {
  builder_rvalue(module, json_get(json, SYMBOL_EXPRESSION));
}
static void builder_jump_statement(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *expr =
        builder_rvalue(module, json_get(json, SYMBOL_EXPRESSION));
    struct json *instr = ir_module_new_instr(module, "ret");
    json_insert(instr, "value", expr);
    json_del(instr);
  }
}
static void builder_statement_list(struct json_map *map) {
  struct json *module = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_statement(module, json);
}

void builder_statement(struct json *module, struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    builder_compound_statement(module,
                               json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_EXPRESSION_STATEMENT)) {
    builder_expression_statement(module,
                                 json_get(json, SYMBOL_EXPRESSION_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    builder_jump_statement(module, json_get(json, SYMBOL_JUMP_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_get(json, SYMBOL_STATEMENT_LIST), builder_statement_list,
                 module);
  }
}
