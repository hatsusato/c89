#include "ast.h"

#include "compare/compare.h"
#include "pool/pool.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

struct struct_Ast {
  Pool *pool;
  Sexp *sexp;
};

static const char *symbol_new(const void *text, Size size) {
  char *symbol = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, symbol, text, size);
  symbol[size] = '\0';
  return symbol;
}
static void symbol_free(VectorElem symbol) {
  UTILITY_FREE(symbol);
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  Compare *cmp = compare_new_strcmp();
  ast->pool = pool_new(symbol_free, cmp);
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
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
  const VectorElem *found;
  assert('\0' == text[leng]);
  found = pool_find(ast->pool, text);
  if (found) {
    return *found;
  } else {
    const char *elem = symbol_new(text, leng);
    pool_insert(ast->pool, elem);
    return elem;
  }
}
