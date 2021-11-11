#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "ir/function.h"
#include "ir/instr.h"
#include "ir/module.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void builder_compound_statement(struct json *function,
                                       struct json *json) {
  ir_function_push_scope(function);
  builder_declaration(function, json);
  builder_statement(function, json);
  ir_function_pop_scope(function);
}
static void builder_expression_statement(struct json *function,
                                         struct json *json) {
  builder_rvalue(function, json_get(json, SYMBOL_EXPRESSION));
}
static void builder_selection_statement(struct json *function,
                                        struct json *json) {
  if (json_has(json, SYMBOL_IF)) {
    struct json *expr =
        builder_rvalue(function, json_get(json, SYMBOL_EXPRESSION));
    struct json *icmp = ir_function_make_instr(function, "icmp");
    struct json *br = ir_function_make_instr(function, "br");
    struct json *block_then = ir_function_make_block(function);
    ir_instr_icmp_cond(icmp, expr);
    json_insert(br, "cond", icmp);
    json_insert(br, "iftrue", block_then);
    builder_statement(function, json_get(json, SYMBOL_THEN_STATEMENT));
    {
      struct json *br_then = ir_function_make_instr(function, "br");
      struct json *block_else = ir_function_make_block(function);
      json_insert(br, "iffalse", block_else);
      if (json_has(json, SYMBOL_ELSE)) {
        builder_statement(function, json_get(json, SYMBOL_ELSE_STATEMENT));
        {
          struct json *br_else = ir_function_make_instr(function, "br");
          struct json *block_after = ir_function_make_block(function);
          json_insert(br_else, "dest", block_after);
          block_else = block_after;
        }
      }
      json_insert(br_then, "dest", block_else);
    }
  }
}
static void builder_jump_statement(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *expr =
        builder_rvalue(function, json_get(json, SYMBOL_EXPRESSION));
    struct json *instr = ir_function_make_instr(function, "ret");
    json_insert(instr, "value", expr);
  }
}
static void builder_statement_list(struct json_map *map) {
  struct json *function = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_statement(function, json);
}

void builder_statement(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    builder_compound_statement(function,
                               json_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_EXPRESSION_STATEMENT)) {
    builder_expression_statement(function,
                                 json_get(json, SYMBOL_EXPRESSION_STATEMENT));
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    builder_selection_statement(function,
                                json_get(json, SYMBOL_SELECTION_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    builder_jump_statement(function, json_get(json, SYMBOL_JUMP_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_get(json, SYMBOL_STATEMENT_LIST), builder_statement_list,
                 function);
  }
}
