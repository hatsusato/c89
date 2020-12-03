#include "ir/declaration.h"

#include "ir/stack_impl.h"

static void stack_declarator(Stack *, Sexp *);
static void stack_direct_declarator(Stack *stack, Sexp *ast) {
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    ast = sexp_at(ast, 1);
    assert(AST_IDENTIFIER == sexp_get_tag(ast));
    ast = sexp_at(ast, 1);
    assert(sexp_get_symbol(ast));
    stack_alloca(stack, sexp_get_symbol(ast));
    break;
  case 4:
    ast = sexp_at(ast, 2);
    stack_declarator(stack, ast);
    break;
  case 5:
    ast = sexp_at(ast, 1);
    stack_direct_declarator(stack, ast);
    break;
  default:
    assert(0);
    break;
  }
}
static void stack_declarator(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  assert(2 == sexp_length(ast) || 3 == sexp_length(ast));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  stack_direct_declarator(stack, ast);
}
static void stack_init_declarator(Stack *stack, Sexp *ast) {
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  if (4 == sexp_length(ast)) {
    stack_declarator(stack, sexp_at(ast, 1));
    stack_ast(stack, sexp_at(ast, 3));
    stack_swap(stack);
    stack_instruction_store(stack);
    stack_pop(stack);
  } else {
    stack_declarator(stack, sexp_at(ast, 1));
    stack_pop(stack);
  }
}
void stack_declaration(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  ast = sexp_at(ast, 2);
  assert(AST_INIT_DECLARATOR_LIST == sexp_get_tag(ast));
  ast = sexp_at(ast, 1);
  stack_init_declarator(stack, ast);
}
