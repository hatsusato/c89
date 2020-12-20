#include "ir/function.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
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
static void function_set_register(Function *func, RegisterGenerator *gen) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  while (begin < end) {
    block_set_register(*begin++, gen);
  }
}
static void function_set_id(Function *func) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  int id = 0;
  while (begin < end) {
    id = block_set_id(*begin++, id);
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
void function_insert(Function *func, Block *block) {
  vector_push(func->vec, block);
}
void function_finish(Function *func) {
  RegisterGenerator *gen = register_generator_new();
  function_set_register(func, gen);
  register_generator_delete(gen);
  function_set_id(func);
}
void function_pretty(Function *func) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  printf("define i32 @%s() {\n", (const char *)func->value);
  assert(begin != end);
  block_pretty(*begin++);
  for (; begin < end; ++begin) {
    printf("\n");
    block_pretty_label(*begin);
    block_pretty(*begin);
  }
  printf("}\n");
}
