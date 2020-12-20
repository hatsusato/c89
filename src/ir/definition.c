#include "ir/definition.h"

#include "ir/block.h"
#include "ir/function.h"
#include "ir/stack_impl.h"

Value *stack_function_definition(Stack *stack, Sexp *ast) {
  stack_build_init(stack, ast);
  {
    Block *ret = stack_get_next(stack, STACK_NEXT_RETURN);
    assert(AST_FUNCTION_DEFINITION == sexp_get_tag(ast));
    assert(5 == sexp_length(ast));
    if (ret) {
      stack_instruction_alloca(stack, "$retval");
    }
    stack_ast(stack, sexp_at(ast, 4));
    if (ret) {
      Value *expr;
      Instruction *instr;
      stack_instruction_br(stack, ret);
      stack_jump_block(stack, ret);
      expr = stack_find_alloca(stack, "$retval");
      instr = stack_instruction_load(stack, expr);
      stack_instruction_ret(stack, instruction_as_value(instr));
    }
  }
  {
    Block *alloc = stack_get_next(stack, STACK_NEXT_ALLOC);
    Block *entry = stack_get_next(stack, STACK_NEXT_ENTRY);
    Function *func = stack_get_function(stack);
    block_append(alloc, entry);
    function_set_id(func);
  }
  stack_build_finish(stack);
  return NULL;
}
