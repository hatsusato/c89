#include "function.h"

#include "ast.h"
#include "block.h"
#include "instruction.h"
#include "print.h"
#include "sexp.h"
#include "utility.h"
#include "value.h"
#include "vector.h"

struct struct_Function {
  const char *name;
  Vector *blocks;
};

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
static const char *function_name(Sexp *ast) {
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
static Sexp *function_body(Sexp *ast) {
  ast = sexp_next(ast, AST_FUNCTION_DEFINITION);
  switch (sexp_length(ast)) {
  case 3:
    return sexp_at(ast, 2);
  case 4:
    return sexp_at(ast, 3);
  default:
    assert(0);
    return NULL;
  }
}
static Function *function_new(void) {
  Function *func = UTILITY_MALLOC(Function);
  func->name = NULL;
  func->blocks = vector_new((Destructor)block_delete);
  return func;
}
static void function_insert(Function *func, Block *block) {
  assert(func);
  vector_push(func->blocks, block);
}
static void function_build_compound_statement(Function *func, Sexp *ast) {
  Block *block;
  Instruction *instr;
  instr = instruction_new(INSTRUCTION_RET);
  instruction_insert(instr, value_new_integer(0));
  block = block_new();
  block_insert(block, instr);
  function_insert(func, block);
  (void)ast;
}

void function_delete(Function *func) {
  assert(func);
  vector_delete(func->blocks);
  UTILITY_FREE(func);
}
Function *function_build(Sexp *ast) {
  Function *func;
  func = function_new();
  func->name = function_name(ast);
  function_build_compound_statement(func, function_body(ast));
  return func;
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
