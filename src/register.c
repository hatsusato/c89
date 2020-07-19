#include "register.h"

#include "ast.h"
#include "sexp.h"
#include "utility.h"

typedef struct {
  SymbolSet *symbols;
  Bool flag;
} Register;

static Bool register_check_tag(Sexp *ast, AstTag tag) {
  return sexp_is_pair(ast) && sexp_is_list(ast) &&
         sexp_get_number(sexp_car(ast)) == (int)tag;
}
static const char *register_from_declarator(Sexp *ast);
static const char *register_from_identifier(Sexp *ast) {
  assert(register_check_tag(ast, AST_IDENTIFIER));
  ast = sexp_at(ast, 1);
  assert(sexp_is_string(ast));
  return sexp_get_string(ast);
}
static const char *register_from_direct_declarator(Sexp *ast) {
  assert(register_check_tag(ast, AST_DIRECT_DECLARATOR));
  ast = sexp_cdr(ast);
  if (register_check_tag(ast, AST_LEFT_PAREN)) {
    return register_from_declarator(sexp_at(ast, 1));
  } else {
    ast = sexp_car(ast);
    if (register_check_tag(ast, AST_IDENTIFIER)) {
      return register_from_identifier(ast);
    } else {
      return register_from_direct_declarator(ast);
    }
  }
}
static const char *register_from_declarator(Sexp *ast) {
  assert(register_check_tag(ast, AST_DECLARATOR));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  return register_from_direct_declarator(ast);
}
static const char *register_from_init_declarator(Sexp *ast) {
  assert(register_check_tag(ast, AST_INIT_DECLARATOR));
  return register_from_declarator(sexp_at(ast, 1));
}

static void register_is_typedef(Register *reg, Sexp *ast) {
  assert(register_check_tag(ast, AST_STORAGE_CLASS_SPECIFIER) ||
         register_check_tag(ast, AST_TYPE_SPECIFIER) ||
         register_check_tag(ast, AST_TYPE_QUALIFIER));
  if (register_check_tag(ast, AST_STORAGE_CLASS_SPECIFIER) &&
      register_check_tag(sexp_cdr(ast), AST_TYPEDEF)) {
    reg->flag = true;
  }
}
static void register_identifier(Register *reg, Sexp *ast) {
  const char *symbol = register_from_init_declarator(ast);
  symbol_register(reg->symbols, symbol, reg->flag);
}
static void register_foreach(Register *reg, Sexp *ast,
                             void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}

void register_declaration(SymbolSet *set, Sexp *sexp) {
  Register reg;
  Sexp *ast = sexp;
  assert(set);
  assert(register_check_tag(ast, AST_DECLARATION));
  reg.symbols = set;
  reg.flag = false;
  ast = sexp_at(sexp, 1);
  assert(register_check_tag(ast, AST_DECLARATION_SPECIFIERS));
  register_foreach(&reg, ast, register_is_typedef);
  ast = sexp_at(sexp, 2);
  assert(register_check_tag(ast, AST_INIT_DECLARATOR_LIST));
  register_foreach(&reg, ast, register_identifier);
}
