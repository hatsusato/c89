#include "function.h"

#include <stdio.h>

#include "ast/tag.h"
#include "block.h"
#include "builder.h"
#include "module.h"
#include "sexp.h"
#include "type.h"
#include "utility.h"
#include "value.h"
#include "vector.h"

struct struct_Function {
  ValueKind kind;
  Type *type;
  const char *name;
  Vector *vec;
};

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->kind = VALUE_FUNCTION;
  func->type = NULL;
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
Type *function_return_type(Function *func) {
  return func->type;
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
  printf("define ");
  type_print(func->type);
  printf(" @%s() {\n", func->name);
  UTILITY_ASSERT(begin != end);
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

Function *builder_new_function(Builder *builder, const char *name, Sexp *ast) {
  Module *module = builder_get_module(builder);
  Function *func = module_new_function(module);
  func->name = name;
  if (5 == sexp_length(ast)) {
    builder_ast(builder, sexp_at(ast, 1));
  }
  func->type = builder_get_type(builder);
  return func;
}
