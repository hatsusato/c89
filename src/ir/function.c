#include "function.h"

#include <stdio.h>

#include "ast/tag.h"
#include "ir/block.h"
#include "ir/module.h"
#include "ir/type.h"
#include "ir/value.h"
#include "sexp/sexp.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Function {
  ValueKind kind;
  Type *type;
  const char *name;
  Vector *vec;
};

Function *function_new(Module *module, const char *name, Type *type) {
  Function *func = UTILITY_MALLOC(Function);
  func->kind = VALUE_FUNCTION;
  func->type = type;
  func->name = name;
  func->vec = vector_new(NULL);
  module_insert_value(module, value_of(func));
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
  VectorElem *begin = vector_begin(func->vec);
  VectorElem *end = vector_end(func->vec);
  int id = 0;
  while (begin < end) {
    id = block_set_id(*begin++, id);
  }
}
void function_pretty(Function *func) {
  VectorElem *begin = vector_begin(func->vec);
  VectorElem *end = vector_end(func->vec);
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
