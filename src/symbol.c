#include "symbol.h"

#include "set.h"
#include "sexp.h"
#include "utility.h"

typedef struct {
  Set *symbols;
  Bool flag;
} Register;

static Symbol *symbol_duplicate(Symbol *src) {
  Symbol *dst = UTILITY_MALLOC(Symbol);
  *dst = *src;
  return dst;
}

Symbol *symbol_new(const char *symbol, Bool flag) {
  Symbol *ptr = UTILITY_MALLOC(Symbol);
  ptr->symbol = symbol;
  ptr->flag = flag;
  return ptr;
}
void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
int symbol_compare(const ElemType *lhs, const ElemType *rhs) {
  const Symbol *l = *lhs;
  const Symbol *r = *rhs;
  return utility_str_cmp(l->symbol, r->symbol);
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
  Symbol symbol;
  symbol.symbol = register_from_init_declarator(ast);
  symbol.flag = reg->flag;
  if (!set_contains(reg->symbols, &symbol)) {
    Bool ret = set_insert(reg->symbols, symbol_duplicate(&symbol));
    assert(ret);
    (void)ret;
  }
}
static void register_foreach(Register *reg, Sexp *ast,
                             void (*map)(Register *, Sexp *)) {
  for (ast = sexp_cdr(ast); sexp_is_pair(ast); ast = sexp_cdr(ast)) {
    map(reg, sexp_car(ast));
  }
}

void symbols_register(Set *symbols, Sexp *sexp) {
  Register reg;
  Sexp *ast = sexp;
  assert(symbols);
  assert(register_check_tag(ast, "declaration"));
  reg.symbols = symbols;
  reg.flag = false;
  ast = sexp_at(sexp, 1);
  assert(register_check_tag(ast, "declaration-specifiers"));
  register_foreach(&reg, ast, register_is_typedef);
  ast = sexp_at(sexp, 2);
  assert(register_check_tag(ast, "init-declarator-list"));
  register_foreach(&reg, ast, register_identifier);
}
