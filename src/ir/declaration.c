#include "ir/declaration.h"

#include "ir/stack_impl.h"

void stack_declaration(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  stack_ast(stack, sexp_at(ast, 2));
}
void stack_init_declarator(Stack *stack, Sexp *ast) {
  Value *src, *dst, *store;
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    stack_declarator(stack, sexp_at(ast, 1));
    stack_pop(stack);
    break;
  case 4:
    stack_ast(stack, sexp_at(ast, 3));
    src = stack_pop(stack);
    stack_declarator(stack, sexp_at(ast, 1));
    dst = stack_pop(stack);
    store = stack_instruction_store(stack, src, dst);
    break;
  default:
    assert(0);
    break;
  }
}
void stack_declarator(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    stack_direct_declarator(stack, sexp_at(ast, 1));
    break;
  case 3:
    stack_direct_declarator(stack, sexp_at(ast, 2));
    break;
  default:
    assert(0);
    break;
  }
}
void stack_direct_declarator(Stack *stack, Sexp *ast) {
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    stack_identifier_alloca(stack, sexp_at(ast, 1));
    break;
  case 4:
    stack_declarator(stack, sexp_at(ast, 2));
    break;
  case 5:
    /* FALLTHROUGH */
  default:
    assert(0);
    break;
  }
}
