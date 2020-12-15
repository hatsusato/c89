#include "ir/declaration.h"

#include "ir/stack_impl.h"

Value *stack_declaration(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 2));
}
Value *stack_init_declarator(Stack *stack, Sexp *ast) {
  Value *src, *dst;
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return stack_declarator(stack, sexp_at(ast, 1));
  case 4:
    stack_ast(stack, sexp_at(ast, 3));
    src = stack_get_prev(stack);
    stack_declarator(stack, sexp_at(ast, 1));
    dst = stack_get_prev(stack);
    return stack_instruction_store(stack, src, dst);
  default:
    assert(0);
    return NULL;
  }
}
Value *stack_declarator(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return stack_direct_declarator(stack, sexp_at(ast, 1));
  case 3:
    return stack_direct_declarator(stack, sexp_at(ast, 2));
  default:
    assert(0);
    return NULL;
  }
}
Value *stack_direct_declarator(Stack *stack, Sexp *ast) {
  const char *symbol;
  Value *alloca;
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    symbol = stack_identifier_symbol(sexp_at(ast, 1));
    alloca = stack_alloca(stack, symbol);
    stack_set_prev(stack, alloca);
    return alloca;
  case 4:
    return stack_declarator(stack, sexp_at(ast, 2));
  case 5:
    /* FALLTHROUGH */
  default:
    assert(0);
    return NULL;
  }
}
