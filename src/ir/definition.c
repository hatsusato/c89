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
static void stack_function_build(Stack *stack, Sexp *ast) {
  Block *ret = stack_get_next(stack, STACK_NEXT_RETURN);
  assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
  assert(5 == sexp_length(ast));
  if (ret) {
    Value *expr;
    Instruction *instr;
    stack_instruction_alloca(stack, "$retval");
    stack_ast(stack, sexp_at(ast, 4));
    stack_instruction_br(stack, ret);
    stack_jump_block(stack, ret);
    expr = stack_find_alloca(stack, "$retval");
    instr = stack_instruction_load(stack, expr);
    stack_instruction_ret(stack, instruction_as_value(instr));
  } else {
    stack_ast(stack, sexp_at(ast, 4));
  }
}

Value *stack_function_definition(Stack *stack, Sexp *ast) {
  Function *func = module_new_function(stack_get_module(stack));
  Block *alloc = stack_new_block(stack);
  Block *entry = stack_new_block(stack);
  Block *ret = 1 < count_return(ast) ? stack_new_block(stack) : NULL;
  stack_set_next(stack, STACK_NEXT_ALLOC, alloc);
  stack_set_next(stack, STACK_NEXT_CURRENT, entry);
  stack_set_next(stack, STACK_NEXT_ENTRY, entry);
  stack_set_next(stack, STACK_NEXT_RETURN, ret);
  stack_function_init(stack, func);
  function_init(func, ast);
  function_insert(func, alloc);
  stack_function_build(stack, ast);
  block_append(alloc, entry);
  function_set_id(func);
  stack_function_finish(stack);
  return NULL;
}
