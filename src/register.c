#include "register.h"

#include "set.h"
#include "sexp.h"
#include "utility.h"

typedef struct {
  const char *symbol;
  Bool flag;
} Symbol;

static Symbol *symbol_new(const char *symbol, Bool flag) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  ptr->symbol = symbol;
  ptr->flag = flag;
  return ptr;
}
static Symbol *symbol_duplicate(const Symbol *src) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  *ptr = *src;
  return ptr;
}
static void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}

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

void register_foreach(Register *reg, Sexp *ast,
                      void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}
void register_is_typedef(Register *reg, Sexp *ast) {
  assert(register_check_tag(ast, "storage-class-specifier") ||
         register_check_tag(ast, "type-specifier") ||
         register_check_tag(ast, "type-qualifier"));
  if (register_check_tag(ast, "storage-class-specifier") &&
      sexp_eq(sexp_at(ast, 1), "typedef")) {
    reg->flag = true;
  }
}
void register_identifier(Register *reg, Sexp *ast) {
  Symbol symbol;
  symbol.symbol = register_from_init_declarator(ast);
  symbol.flag = reg->flag;
  if (!set_contains(reg->symbols, &symbol)) {
    Bool ret = set_insert(reg->symbols, symbol_duplicate(&symbol));
    assert(ret);
    (void)ret;
  }
}
