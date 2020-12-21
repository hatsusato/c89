#include "ir/function.h"

#include <stdio.h>

#include "ast/ast_tag.h"
#include "ir/block.h"
#include "ir/builder.h"
#include "ir/module.h"
#include "ir/value_kind.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Function {
  ValueKind kind;
  const char *name;
  Vector *vec;
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
  func->name = NULL;
  func->vec = vector_new(NULL);
  return func;
}
void function_delete(Function *func) {
  vector_delete(func->vec);
  UTILITY_FREE(func);
}
void function_insert(Function *func, Block *block) {
  vector_push(func->vec, block);
}
void function_set_id(Function *func) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  int id = 0;
  while (begin < end) {
    id = block_set_id(*begin++, id);
  }
}
void function_pretty(Function *func) {
  ElemType *begin = vector_begin(func->vec);
  ElemType *end = vector_end(func->vec);
  printf("define i32 @%s() {\n", func->name);
  assert(begin != end);
  block_pretty(*begin++);
  for (; begin < end; ++begin) {
    printf("\n");
    block_print_label(*begin);
    block_pretty(*begin);
  }
  printf("}\n");
}
int function_count_return(Sexp *ast) {
  if (sexp_is_pair(ast)) {
    return function_count_return(sexp_car(ast)) +
           function_count_return(sexp_cdr(ast));
  } else {
    return sexp_is_number(ast) && AST_RETURN == sexp_get_number(ast);
  }
}

Function *builder_new_function(Builder *builder, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Function *func = module_new_function(module);
  func->name = function_name(ast);
  return func;
}
