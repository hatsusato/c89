#include "ast.h"

#include "compare.h"
#include "set/pool.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"

struct struct_Ast {
  Pool *symbols;
  Sexp *sexp;
};

static int symbol_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  (void)extra;
  return utility_strcmp(lhs, rhs);
}
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
  Vector *vec = vector_new(symbol_free);
  Compare *cmp = compare_new(symbol_compare);
  ast->symbols = pool_new(vec, cmp);
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
  pool_delete(ast->symbols);
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
  found = pool_find(ast->symbols, (ElemType)text);
  if (found) {
    return *found;
  } else {
    ElemType elem = (ElemType)symbol_new(text, leng);
    pool_insert(ast->symbols, elem);
    return elem;
  }
}
