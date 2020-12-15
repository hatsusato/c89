#include "ir/declaration.h"

#include "ir/stack_impl.h"

Value *stack_declaration(Stack *stack, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  return stack_ast(stack, sexp_at(ast, 2));
}
Value *stack_init_declarator(Stack *stack, Sexp *ast) {
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return stack_declarator(stack, sexp_at(ast, 1));
  case 4: {
    Value *src = stack_ast(stack, sexp_at(ast, 3));
    Value *dst = stack_declarator(stack, sexp_at(ast, 1));
    return stack_instruction_store(stack, src, dst);
  }
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
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2: {
    const char *symbol = stack_identifier_symbol(sexp_at(ast, 1));
    return stack_alloca(stack, symbol);
  }
  case 4:
    return stack_declarator(stack, sexp_at(ast, 2));
  case 5:
    /* FALLTHROUGH */
  default:
    assert(0);
    return NULL;
  }
}
