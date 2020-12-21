#include "ir/declaration.h"

#include "ir/stack_impl.h"

Value *builder_declaration(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATION == sexp_get_tag(ast));
  return builder_ast(builder, sexp_at(ast, 2));
}
Value *builder_init_declarator(Builder *builder, Sexp *ast) {
  assert(AST_INIT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_declarator(builder, sexp_at(ast, 1));
  case 4: {
    Value *src = builder_ast(builder, sexp_at(ast, 3));
    Value *dst = builder_declarator(builder, sexp_at(ast, 1));
    Instruction *instr = builder_instruction_store(builder, src, dst);
    return instruction_as_value(instr);
  }
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_declarator(Builder *builder, Sexp *ast) {
  assert(AST_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2:
    return builder_direct_declarator(builder, sexp_at(ast, 1));
  case 3:
    return builder_direct_declarator(builder, sexp_at(ast, 2));
  default:
    assert(0);
    return NULL;
  }
}
Value *builder_direct_declarator(Builder *builder, Sexp *ast) {
  assert(AST_DIRECT_DECLARATOR == sexp_get_tag(ast));
  switch (sexp_length(ast)) {
  case 2: {
    const char *symbol = builder_identifier_symbol(sexp_at(ast, 1));
    Instruction *instr = builder_instruction_alloca(builder, symbol);
    return instruction_as_value(instr);
  }
  case 4:
    return builder_declarator(builder, sexp_at(ast, 2));
  case 5:
    /* FALLTHROUGH */
  default:
    assert(0);
    return NULL;
  }
}
