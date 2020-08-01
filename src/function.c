#include "function.h"

#include "ast.h"
#include "block.h"
#include "print.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Function {
  const char *name;
  Vector *blocks;
};

static void function_set_declarator(Function *, Sexp *);
static void function_set_identifier(Function *func, Sexp *ast) {
  ast = sexp_next(ast, AST_IDENTIFIER);
  ast = sexp_car(ast);
  assert(sexp_is_string(ast));
  func->name = sexp_get_string(ast);
}
static void function_set_direct_declarator(Function *func, Sexp *ast) {
  ast = sexp_next(ast, AST_DIRECT_DECLARATOR);
  switch (ast_get(ast)) {
  case AST_IDENTIFIER:
    function_set_identifier(func, sexp_at(ast, 0));
    break;
  case AST_LEFT_PAREN:
    function_set_declarator(func, sexp_at(ast, 1));
    break;
  case AST_DIRECT_DECLARATOR:
    function_set_direct_declarator(func, sexp_at(ast, 0));
    break;
  default:
    assert(0);
  }
}
static void function_set_declarator(Function *func, Sexp *ast) {
  ast = sexp_next(ast, AST_DECLARATOR);
  switch (sexp_length(ast)) {
  case 1:
    function_set_direct_declarator(func, sexp_at(ast, 0));
    break;
  case 2:
    function_set_direct_declarator(func, sexp_at(ast, 1));
    break;
  default:
    assert(0);
  }
}
static const char *function_name_from_declarator(Sexp *);
static const char *function_name_from_identifier(Sexp *ast) {
  ast = sexp_next(ast, AST_IDENTIFIER);
  ast = sexp_car(ast);
  assert(sexp_is_string(ast));
  return sexp_get_string(ast);
}
static const char *function_name_from_direct_declarator(Sexp *ast) {
  ast = sexp_next(ast, AST_DIRECT_DECLARATOR);
  switch (ast_get(ast)) {
  case AST_IDENTIFIER:
    return function_name_from_identifier(sexp_at(ast, 0));
  case AST_LEFT_PAREN:
    return function_name_from_declarator(sexp_at(ast, 1));
  case AST_DIRECT_DECLARATOR:
    return function_name_from_direct_declarator(sexp_at(ast, 0));
  default:
    assert(0);
    return NULL;
  }
}
static const char *function_name_from_declarator(Sexp *ast) {
  ast = sexp_next(ast, AST_DECLARATOR);
  switch (sexp_length(ast)) {
  case 1:
    return function_name_from_direct_declarator(sexp_at(ast, 0));
  case 2:
    return function_name_from_direct_declarator(sexp_at(ast, 1));
  default:
    assert(0);
    return NULL;
  }
}

Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->name = NULL;
  func->blocks = vector_new((Destructor)block_delete);
  return func;
}
void function_delete(Function *func) {
  assert(func);
  vector_delete(func->blocks);
  UTILITY_FREE(func);
}
void function_insert(Function *func, Block *block) {
  assert(func);
  vector_push(func->blocks, block);
}
const char *function_name(Sexp *ast) {
  ast = sexp_next(ast, AST_FUNCTION_DEFINITION);
  switch (sexp_length(ast)) {
  case 3:
    return function_name_from_declarator(sexp_at(ast, 0));
  case 4:
    return function_name_from_declarator(sexp_at(ast, 1));
  default:
    assert(0);
    return NULL;
  }
}
void function_set_name(Function *func, const char *name) {
  assert(func);
  func->name = name;
}
void function_set(Function *func, Sexp *ast) {
  ast = sexp_next(ast, AST_FUNCTION_DEFINITION);
  assert(4 == sexp_length(ast));
  function_set_declarator(func, sexp_at(ast, 1));
}
void function_print(FILE *fp, Function *func) {
  ElemType *it;
  assert(func);
  print_message(fp, "define i32 @");
  print_message(fp, func->name);
  print_message(fp, "() {\n");
  for (it = vector_begin(func->blocks); it != vector_end(func->blocks); ++it) {
    block_print(fp, (Block *)*it);
  }
  print_message(fp, "}\n");
}
