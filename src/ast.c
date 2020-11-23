#include "ast.h"

#include "sexp.h"
#include "utility.h"
#include "vector/pool.h"

struct struct_Ast {
  Pool *symbols;
  Sexp *sexp;
};

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  ast->symbols = pool_new();
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
  assert('\0' == text[leng]);
  return pool_insert(ast->symbols, text, leng + 1);
}
