#include "register.h"

#include "ast.h"
#include "scanner.h"
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

static Bool is_typedef_storage_class_specifier(Sexp *ast) {
  assert(check_tag(ast, AST_STORAGE_CLASS_SPECIFIER));
  ast = sexp_at(ast, 1);
  return check_tag(ast, AST_TYPEDEF);
}
static Bool is_typedef_declaration_specifier(Sexp *ast) {
  if (check_tag(ast, AST_STORAGE_CLASS_SPECIFIER)) {
    return is_typedef_storage_class_specifier(ast);
  } else {
    assert(check_tag(ast, AST_TYPE_SPECIFIER));
    assert(check_tag(ast, AST_TYPE_QUALIFIER));
    return false;
  }
}
static Bool is_typedef_declaration_specifiers(Sexp *ast) {
  assert(check_tag(ast, AST_DECLARATION_SPECIFIERS));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    if (is_typedef_declaration_specifier(sexp_car(ast))) {
      return true;
    }
  }
  return false;
}
static Bool is_typedef_declaration(Sexp *ast) {
  assert(check_tag(ast, AST_DECLARATION));
  ast = sexp_at(ast, 1);
  return is_typedef_declaration_specifiers(ast);
}

static void register_identifier(Scanner *scanner, Sexp *ast, Bool flag) {
  assert(check_tag(ast, AST_IDENTIFIER));
  ast = sexp_at(ast, 1);
  assert(sexp_is_string(ast));
  scanner_register(scanner, sexp_get_string(ast), flag);
}
static void register_declarator(Scanner *, Sexp *, Bool);
static void register_direct_declarator(Scanner *scanner, Sexp *ast, Bool flag) {
  Sexp *next;
  assert(check_tag(ast, AST_DIRECT_DECLARATOR));
  next = sexp_at(ast, 1);
  if (check_tag(next, AST_LEFT_PAREN)) {
    next = sexp_at(ast, 2);
    register_declarator(scanner, next, flag);
  } else if (check_tag(next, AST_IDENTIFIER)) {
    register_identifier(scanner, next, flag);
  } else {
    register_direct_declarator(scanner, next, flag);
  }
}
static void register_declarator(Scanner *scanner, Sexp *ast, Bool flag) {
  Sexp *next;
  assert(check_tag(ast, AST_DECLARATOR));
  next = sexp_at(ast, 1);
  if (check_tag(next, AST_POINTER)) {
    next = sexp_at(ast, 2);
  }
  register_direct_declarator(scanner, next, flag);
}
static void register_init_declarator(Scanner *scanner, Sexp *ast, Bool flag) {
  assert(check_tag(ast, AST_INIT_DECLARATOR));
  ast = sexp_at(ast, 1);
  register_declarator(scanner, ast, flag);
}
static void register_init_declarator_list(Scanner *scanner, Sexp *ast,
                                          Bool flag) {
  assert(check_tag(ast, AST_INIT_DECLARATOR_LIST));
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    register_init_declarator(scanner, sexp_car(ast), flag);
  }
}
void register_declaration(Scanner *scanner, Sexp *ast) {
  assert(check_tag(ast, AST_DECLARATION));
  if (is_typedef_declaration(ast)) {
    ast = sexp_at(ast, 2);
    register_init_declarator_list(scanner, ast, true);
  } else {
    ast = sexp_at(ast, 2);
    register_init_declarator_list(scanner, ast, false);
  }
}
