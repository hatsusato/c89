#include "ast.h"

#include "compare.h"
#include "pool.h"
#include "set.h"
#include "sexp.h"
#include "utility.h"

struct struct_Ast {
  Pool *pool;
  Set *symbols;
  Sexp *sexp;
};

static const char *symbol_new(const void *text, Size size) {
  char *symbol = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, symbol, text, size);
  symbol[size] = '\0';
  return symbol;
}
static void symbol_free(ElemType symbol) {
  UTILITY_FREE(symbol);
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  Compare *cmp = compare_new_strcmp();
  ast->pool = pool_new(symbol_free, cmp);
  ast->symbols = set_new(symbol_free, compare_new_strcmp());
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
  set_delete(ast->symbols);
  pool_delete(ast->pool);
  UTILITY_FREE(ast);
}
Sexp *ast_get(Ast *ast) {
  return ast->sexp;
}
void ast_set(Ast *ast, Sexp *sexp) {
  assert(sexp_is_nil(ast->sexp));
  ast->sexp = sexp;
}
const char *ast_symbol(Ast *ast, const char *text, Size leng) {
  const ElemType *found;
  assert('\0' == text[leng]);
  found = set_find(ast->symbols, (ElemType)text);
  if (found) {
    return *found;
  } else {
    ElemType elem = (ElemType)symbol_new(text, leng);
    set_insert(ast->symbols, elem);
    return elem;
  }
}
