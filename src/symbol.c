#include "symbol.h"

#include "register.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

Symbol *symbol_new(Symbol *src) {
  Symbol *dst = UTILITY_MALLOC(Symbol);
  *dst = *src;
  return dst;
}
void symbol_delete(Symbol *symbol) {
  UTILITY_FREE(symbol);
}
int symbol_compare(const ElemType *lhs, const ElemType *rhs) {
  const Symbol *l = *lhs;
  const Symbol *r = *rhs;
  return utility_str_cmp(l->symbol, r->symbol);
}
Bool symbol_flag(const Symbol *symbol) {
  assert(symbol);
  return symbol->flag;
}

void symbol_init(Set *set) {
  Symbol symbol;
  symbol.symbol = "__builtin_va_list";
  symbol.flag = true;
  set_insert(set, symbol_new(&symbol));
}
void symbol_register(Set *set, Sexp *sexp) {
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
const Symbol *symbol_query(const Set *set, const char *sym) {
  Symbol symbol;
  const ElemType *found;
  symbol.symbol = sym;
  symbol.flag = false;
  found = set_find(set, &symbol);
  return found ? *found : NULL;
}
