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

static Bool is_typedef_storage_class_specifier(Sexp *ast) {
  assert(check_tag(ast, AST_STORAGE_CLASS_SPECIFIER));
  ast = sexp_at(ast, 1);
  return check_tag(ast, AST_TYPEDEF);
}
static Bool is_typedef_declaration_specifier(Sexp *ast) {
  if (check_tag(ast, AST_STORAGE_CLASS_SPECIFIER)) {
    return is_typedef_storage_class_specifier(ast);
  } else {
    assert(check_tag(ast, AST_TYPE_SPECIFIER) ||
           check_tag(ast, AST_TYPE_QUALIFIER));
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
