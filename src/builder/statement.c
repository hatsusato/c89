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

static void builder_labeled_statement(struct json *function,
                                      struct json *json) {
  if (json_has(json, SYMBOL_DEFAULT)) {
    builder_statement(function, json_obj_get(json, SYMBOL_STATEMENT));
  }
}
static void builder_compound_statement(struct json *function,
                                       struct json *json) {
  ir_function_push_scope(function);
  builder_declaration(function, json);
  builder_statement(function, json);
  ir_function_pop_scope(function);
}
static void builder_expression_statement(struct json *function,
                                         struct json *json) {
  builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
}
static struct json *builder_statement_next_block(struct json *function,
                                                 struct json *json) {
  struct json *next = ir_block_new();
  ir_function_next_block(function, next);
  builder_statement(function, json);
  json_del(next);
  return next;
}
static void builder_selection_statement(struct json *function,
                                        struct json *json) {
  struct json *old_next = ir_function_get_next(function);
  if (json_has(json, SYMBOL_IF)) {
    struct json *block_prev = ir_function_get_block(function);
    struct json *expr =
        builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
    struct json *icmp = ir_function_make_instr(function, "icmp");
    struct json *br = ir_block_make_terminator(block_prev, "br");
    struct json *block_next = ir_block_new();
    ir_instr_icmp_cond(icmp, expr);
    ir_function_set_next(function, block_next);
    {
      struct json *block_then = builder_statement_next_block(
          function, json_obj_get(json, SYMBOL_THEN_STATEMENT));
      struct json *block_else = block_next;
      if (json_has(json, SYMBOL_ELSE)) {
        block_else = builder_statement_next_block(
            function, json_obj_get(json, SYMBOL_ELSE_STATEMENT));
      }
      ir_instr_insert(br, "cond", icmp);
      ir_instr_insert(br, "iftrue", block_then);
      ir_instr_insert(br, "iffalse", block_else);
      if (!json_has(json, SYMBOL_MUST_RETURN)) {
        ir_function_next_block(function, block_next);
      }
    }
    json_del(block_next);
  } else if (json_has(json, SYMBOL_SWITCH)) {
    struct json *block_prev = ir_function_get_block(function);
    struct json *expr =
        builder_rvalue(function, json_obj_get(json, SYMBOL_EXPRESSION));
    struct json *terminator = ir_block_make_terminator(block_prev, "switch");
    struct json *block_default = builder_statement_next_block(
        function, json_obj_get(json, SYMBOL_STATEMENT));
    struct json *block_next = ir_block_new();
    json_obj_insert(terminator, "value", expr);
    json_obj_insert(terminator, "default", block_default);
    ir_function_next_block(function, block_next);
    json_del(block_next);
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
