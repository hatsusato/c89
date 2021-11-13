#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "ir/block.h"
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
static void builder_statement_set_terminator_dest(struct json *block_before,
                                                  struct json *block_after) {
  struct json *br = ir_block_new_terminator(block_before, "br");
  ir_instr_insert(br, "dest", block_after);
  json_del(br);
}
static void builder_selection_statement(struct json *function,
                                        struct json *json) {
  if (json_has(json, SYMBOL_IF)) {
    struct json *block = ir_function_get_block(function);
    struct json *br = ir_block_new_terminator(block, "br");
    struct json *expr =
        builder_rvalue(function, json_get(json, SYMBOL_EXPRESSION));
    struct json *icmp = ir_function_make_instr(function, "icmp");
    ir_instr_icmp_cond(icmp, expr);
    ir_instr_insert(br, "cond", icmp);
    {
      struct json *block_then, *block_else = json_null();
      block_then = ir_function_make_block(function);
      builder_statement(function, json_get(json, SYMBOL_THEN_STATEMENT));
      if (json_has(json, SYMBOL_ELSE)) {
        block_else = ir_function_make_block(function);
        builder_statement(function, json_get(json, SYMBOL_ELSE_STATEMENT));
      }
      {
        struct json *block_before = ir_function_get_block(function);
        struct json *block_after = ir_function_make_block(function);
        builder_statement_set_terminator_dest(block_before, block_after);
        if (json_has(json, SYMBOL_ELSE)) {
          builder_statement_set_terminator_dest(block_then, block_after);
        } else {
          block_else = block_after;
        }
      }
      ir_instr_insert(br, "iftrue", block_then);
      ir_instr_insert(br, "iffalse", block_else);
    }
    json_del(br);
  }
}
static void builder_jump_statement(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *block = ir_function_get_block(function);
    struct json *instr = ir_block_new_terminator(block, "ret");
    struct json *expr =
        builder_rvalue(function, json_get(json, SYMBOL_EXPRESSION));
    ir_instr_insert(instr, "value", expr);
    json_del(instr);
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
