#include "ast.h"

#include "compare.h"
#include "sexp.h"
#include "utility.h"
#include "vector.h"
#include "vector/pool.h"

struct struct_Ast {
  Pool *symbols;
  Sexp *sexp;
};

static int pool_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  (void)extra;
  return utility_strcmp(lhs, rhs);
}
static const char *entry_constructor(const void *buf, Size size) {
  char *entry = UTILITY_MALLOC_ARRAY(char, size);
  UTILITY_MEMCPY(Byte, entry, buf, size);
  return entry;
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  Vector *vec = vector_new(utility_free);
  Compare *cmp = compare_new(pool_compare);
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
    ElemType elem = (ElemType)entry_constructor(text, leng + 1);
    pool_insert(ast->symbols, elem);
    return elem;
  }
}
