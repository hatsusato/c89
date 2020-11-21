#include "register.h"

#include "ast.h"
#include "sexp.h"
#include "utility.h"

static Bool check_tag(Sexp *ast, AstTag tag) {
  if (sexp_is_pair(ast)) {
    assert(sexp_is_list(ast));
    ast = sexp_car(ast);
  }
  return sexp_get_number(ast) == (int)tag;
}
static const char *from_declarator(Sexp *ast);
static const char *from_identifier(Sexp *ast) {
  assert(check_tag(ast, AST_IDENTIFIER));
  ast = sexp_at(ast, 1);
  assert(sexp_is_string(ast));
  return sexp_get_string(ast);
}
static const char *from_direct_declarator(Sexp *ast) {
  assert(check_tag(ast, AST_DIRECT_DECLARATOR));
  ast = sexp_cdr(ast);
  if (check_tag(ast, AST_LEFT_PAREN)) {
    return from_declarator(sexp_at(ast, 1));
  } else {
    ast = sexp_car(ast);
    if (check_tag(ast, AST_IDENTIFIER)) {
      return from_identifier(ast);
    } else {
      return from_direct_declarator(ast);
    }
  }
}
static const char *from_declarator(Sexp *ast) {
  assert(check_tag(ast, AST_DECLARATOR));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  return from_direct_declarator(ast);
}
static const char *from_init_declarator(Sexp *ast) {
  assert(check_tag(ast, AST_INIT_DECLARATOR));
  return from_declarator(sexp_at(ast, 1));
}

typedef struct {
  SymbolSet *symbols;
  Bool flag;
} Register;

static void reg_is_typedef(Register *reg, Sexp *ast) {
  assert(check_tag(ast, AST_STORAGE_CLASS_SPECIFIER) ||
         check_tag(ast, AST_TYPE_SPECIFIER) ||
         check_tag(ast, AST_TYPE_QUALIFIER));
  if (check_tag(ast, AST_STORAGE_CLASS_SPECIFIER) &&
      check_tag(sexp_cdr(ast), AST_TYPEDEF)) {
    reg->flag = true;
  }
}
static void reg_identifier(Register *reg, Sexp *ast) {
  const char *symbol = from_init_declarator(ast);
  symbol_register(reg->symbols, symbol, reg->flag);
}
static void reg_foreach(Register *reg, Sexp *ast,
                        void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}

void reg_declaration(SymbolSet *set, Sexp *sexp) {
  Register reg;
  Sexp *ast = sexp;
  assert(set);
  assert(check_tag(ast, AST_DECLARATION));
  reg.symbols = set;
  reg.flag = false;
  ast = sexp_at(sexp, 1);
  assert(check_tag(ast, AST_DECLARATION_SPECIFIERS));
  reg_foreach(&reg, ast, reg_is_typedef);
  ast = sexp_at(sexp, 2);
  assert(check_tag(ast, AST_INIT_DECLARATOR_LIST));
  reg_foreach(&reg, ast, reg_identifier);
}
