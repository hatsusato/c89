#include "statement.h"

#include "declaration.h"
#include "expression.h"
#include "ir/block.h"
#include "ir/function.h"
#include "ir/instr.h"
#include "ir/module.h"
#include "ir/switch.h"
#include "ir/table.h"
#include "json/json.h"
#include "json/map.h"
#include "util/symbol.h"

static void builder_labeled_statement(struct json *function,
                                      struct json *json) {
  struct json *switch_extra = ir_function_get_switch(function);
  struct json *block = ir_block_new();
  ir_function_advance_next(function, block);
  builder_statement(function, json_obj_get(json, SYMBOL_STATEMENT));
  if (false) {
  } else if (json_has(json, SYMBOL_CASE)) {
    struct json *constant = json_obj_get(json, SYMBOL_CONSTANT_EXPRESSION);
    ir_switch_insert_case(switch_extra, constant, block);
  } else if (json_has(json, SYMBOL_DEFAULT)) {
    ir_switch_insert_default(switch_extra, block);
  }
  json_del(block);
}
static void builder_compound_statement(struct json *function,
                                       struct json *json) {
  struct json *table = ir_function_get_table(function);
  ir_table_push(table);
  builder_declaration(function, json);
  builder_statement(function, json);
  ir_table_pop(table);
}
static void builder_expression_statement(struct json *function,
                                         struct json *json) {
  builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
}
static void builder_selection_statement_if(struct json *function,
                                           struct json *json, struct json *br) {
  struct json *block_next = ir_block_new();
  ir_function_set_next(function, block_next);
  {
    struct json *block_then = ir_block_new();
    struct json *block_else = json_null();
    ir_function_advance_next(function, block_then);
    builder_statement(function, json_obj_get(json, SYMBOL_THEN_STATEMENT));
    if (json_has(json, SYMBOL_ELSE)) {
      block_else = ir_block_new();
      ir_function_advance_next(function, block_else);
      builder_statement(function, json_obj_get(json, SYMBOL_ELSE_STATEMENT));
    }
    ir_instr_insert(br, "iftrue", block_then);
    ir_instr_insert(br, "iffalse",
                    json_is_null(block_else) ? block_next : block_else);
    json_del(block_else);
    json_del(block_then);
    if (!json_has(json, SYMBOL_MUST_RETURN)) {
      ir_function_advance_next(function, block_next);
    }
  }
  json_del(block_next);
}
static void builder_selection_statement_switch(struct json *function,
                                               struct json *json,
                                               struct json *switch_extra) {
  struct json *block_next = ir_block_new();
  ir_function_set_switch(function, switch_extra);
  ir_switch_insert_default(switch_extra, block_next);
  builder_statement(function, json_obj_get(json, SYMBOL_STATEMENT));
  ir_function_advance_next(function, block_next);
  json_del(block_next);
}
static void builder_selection_statement(struct json *function,
                                        struct json *json) {
  struct json *old_next = ir_function_get_next(function);
  struct json *block_prev = ir_function_get_block(function);
  struct json *expr =
      builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
  if (json_has(json, SYMBOL_IF)) {
    struct json *icmp = ir_function_make_instr(function, "icmp");
    struct json *br = ir_block_make_terminator(block_prev, "br");
    ir_instr_icmp_cond(icmp, expr);
    ir_instr_insert(br, "cond", icmp);
    builder_selection_statement_if(function, json, br);
  } else if (json_has(json, SYMBOL_SWITCH)) {
    struct json *switch_old = ir_function_get_switch(function);
    struct json *terminator = ir_block_make_terminator(block_prev, "switch");
    struct json *switch_extra = ir_switch_new(terminator);
    json_obj_insert(terminator, SYMBOL_INSTR_SWITCH_VALUE, expr);
    builder_selection_statement_switch(function, json, switch_extra);
    ir_switch_del(switch_extra);
    ir_function_set_switch(function, switch_old);
  }
  ir_function_set_next(function, old_next);
}
static void builder_jump_statement(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_RETURN)) {
    struct json *block = ir_function_get_block(function);
    struct json *instr = ir_block_make_terminator(block, "ret");
    struct json *expr =
        builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
    ir_instr_insert(instr, "value", expr);
    ir_function_push_return_block(function, block);
  }
}
static void builder_statement_list(struct json_map *map) {
  struct json *function = json_map_extra(map);
  struct json *json = json_map_val(map);
  builder_statement(function, json);
}

void builder_statement(struct json *function, struct json *json) {
  if (json_has(json, SYMBOL_LABELED_STATEMENT)) {
    builder_labeled_statement(function,
                              json_obj_get(json, SYMBOL_LABELED_STATEMENT));
  } else if (json_has(json, SYMBOL_COMPOUND_STATEMENT)) {
    builder_compound_statement(function,
                               json_obj_get(json, SYMBOL_COMPOUND_STATEMENT));
  } else if (json_has(json, SYMBOL_EXPRESSION_STATEMENT)) {
    builder_expression_statement(
        function, json_obj_get(json, SYMBOL_EXPRESSION_STATEMENT));
  } else if (json_has(json, SYMBOL_SELECTION_STATEMENT)) {
    builder_selection_statement(function,
                                json_obj_get(json, SYMBOL_SELECTION_STATEMENT));
  } else if (json_has(json, SYMBOL_JUMP_STATEMENT)) {
    builder_jump_statement(function, json_obj_get(json, SYMBOL_JUMP_STATEMENT));
  } else if (json_has(json, SYMBOL_STATEMENT_LIST)) {
    json_foreach(json_obj_get(json, SYMBOL_STATEMENT_LIST),
                 builder_statement_list, function);
  }
}
