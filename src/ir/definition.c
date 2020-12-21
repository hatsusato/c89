#include "ir/definition.h"

#include "ir/block.h"
#include "ir/function.h"
#include "ir/module.h"
#include "ir/stack.h"
#include "ir/stack_impl.h"

static int count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return count_return(sexp_car(ast)) + count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}
static void builder_function_build(Builder *builder, Sexp *ast) {
  Block *ret = builder_get_next(builder, BUILDER_NEXT_RETURN);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (ret) {
    Value *expr;
    Instruction *instr;
    builder_instruction_alloca(builder, "$retval");
    builder_ast(builder, sexp_at(ast, 4));
    builder_instruction_br(builder, ret);
    builder_jump_block(builder, ret);
    expr = builder_find_alloca(builder, "$retval");
    instr = builder_instruction_load(builder, expr);
    builder_instruction_ret(builder, instruction_as_value(instr));
  } else {
    builder_ast(builder, sexp_at(ast, 4));
  }
}

Value *builder_function_definition(Builder *builder, Sexp *ast) {
  Function *func = module_new_function(builder_get_module(builder));
  Block *alloc = builder_new_block(builder);
  Block *entry = builder_new_block(builder);
  Block *ret = 1 < count_return(ast) ? builder_new_block(builder) : NULL;
  builder_set_next(builder, BUILDER_NEXT_ALLOC, alloc);
  builder_set_next(builder, BUILDER_NEXT_CURRENT, entry);
  builder_set_next(builder, BUILDER_NEXT_ENTRY, entry);
  builder_set_next(builder, BUILDER_NEXT_RETURN, ret);
  builder_function_init(builder, func);
  function_init(func, ast);
  function_insert(func, alloc);
  builder_function_build(builder, ast);
  block_append(alloc, entry);
  function_set_id(func);
  builder_function_finish(builder);
  return NULL;
}
