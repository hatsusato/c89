#include "register.h"

#include "sexp.h"
#include "utility.h"

typedef struct {
  SymbolSet *symbols;
  Bool flag;
} Register;

static Bool register_check_tag(Sexp *ast, const char *tag) {
  return sexp_is_pair(ast) && sexp_is_list(ast) && sexp_eq(sexp_car(ast), tag);
}
static const char *register_from_declarator(Sexp *ast);
static const char *register_from_identifier(Sexp *ast) {
  assert(register_check_tag(ast, "identifier"));
  ast = sexp_at(ast, 1);
  assert(sexp_is_string(ast));
  return sexp_get(ast);
}
static const char *register_from_direct_declarator(Sexp *ast) {
  assert(register_check_tag(ast, "direct-declarator"));
  ast = sexp_cdr(ast);
  if (register_check_tag(ast, "(")) {
    return register_from_declarator(sexp_at(ast, 1));
  } else {
    ast = sexp_car(ast);
    if (register_check_tag(ast, "identifier")) {
      return register_from_identifier(ast);
    } else {
      return register_from_direct_declarator(ast);
    }
  }
}
static const char *register_from_declarator(Sexp *ast) {
  assert(register_check_tag(ast, "declarator"));
  ast = sexp_at(ast, sexp_length(ast) - 1);
  return register_from_direct_declarator(ast);
}
static const char *register_from_init_declarator(Sexp *ast) {
  assert(register_check_tag(ast, "init-declarator"));
  return register_from_declarator(sexp_at(ast, 1));
}

static void register_is_typedef(Register *reg, Sexp *ast) {
  assert(register_check_tag(ast, "storage-class-specifier") ||
         register_check_tag(ast, "type-specifier") ||
         register_check_tag(ast, "type-qualifier"));
  if (register_check_tag(ast, "storage-class-specifier") &&
      sexp_eq(sexp_at(ast, 1), "typedef")) {
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
  assert(register_check_tag(ast, "declaration"));
  reg.symbols = set;
  reg.flag = false;
  ast = sexp_at(sexp, 1);
  assert(register_check_tag(ast, "declaration-specifiers"));
  register_foreach(&reg, ast, register_is_typedef);
  ast = sexp_at(sexp, 2);
  assert(register_check_tag(ast, "init-declarator-list"));
  register_foreach(&reg, ast, register_identifier);
}
