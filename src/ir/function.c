#include "ir/function.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/register.h"
#include "ir/value.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Function {
  ValueKind kind;
  Register reg;
  Vector *vec;
  const void *value;
};
static const char *function_name(Sexp *ast) {
  switch (sexp_get_tag(ast)) {
  case AST_IDENTIFIER:
    ast = sexp_at(ast, 1);
    assert(sexp_is_symbol(ast));
    return sexp_get_symbol(ast);
  case AST_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return function_name(sexp_at(ast, 1));
    case 3:
      return function_name(sexp_at(ast, 2));
    default:
      assert(0);
      return NULL;
    }
  case AST_DIRECT_DECLARATOR:
    switch (sexp_length(ast)) {
    case 2:
      return function_name(sexp_at(ast, 1));
    case 4:
      return function_name(sexp_at(ast, 2));
    case 5:
      return function_name(sexp_at(ast, 1));
    default:
      assert(0);
      return NULL;
    }
  case AST_FUNCTION_DEFINITION:
    assert(5 == sexp_length(ast));
    return function_name(sexp_at(ast, 2));
  default:
    assert(0);
    return NULL;
  }
}

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->kind = VALUE_FUNCTION;
  register_init(&func->reg);
  func->vec = vector_new(NULL);
  func->value = NULL;
  return func;
}
void function_delete(Function *func) {
  vector_delete(func->vec);
  UTILITY_FREE(func);
}
void function_init(Function *func, Sexp *ast) {
  func->value = function_name(ast);
}
void function_insert(Function *func, Value *block) {
  vector_push(func->vec, block);
}
void function_finish(Function *func) {
  RegisterGenerator *gen = register_generator_new();
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  while (begin < end) {
    value_set_reg(gen, *begin++);
  }
  register_generator_delete(gen);
}
void function_pretty(Function *func) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  printf("define i32 @%s() {\n", (const char *)func->value);
  assert(begin != end);
  value_pretty(*begin++);
  for (; begin < end; ++begin) {
    printf("\n");
    value_print_block_label(*begin);
    value_pretty(*begin);
  }
  printf("}\n");
}
