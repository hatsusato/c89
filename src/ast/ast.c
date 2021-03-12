#include "ast.h"

#include "compare/compare.h"
#include "set/set.h"
#include "sexp/sexp.h"
#include "utility/utility.h"

struct struct_Ast {
  Set *pool;
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
  ast->pool = set_new(symbol_free, NULL);
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
  set_delete(ast->pool);
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
  const CompareElem *found;
  assert('\0' == text[leng]);
  found = set_find(ast->pool, text);
  if (found) {
    return *found;
  } else {
    const char *elem = symbol_new(text, leng);
    set_insert(ast->pool, elem);
    return elem;
  }
}
