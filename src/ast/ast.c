#include "ast.h"

#include "compare.h"
#include "sexp.h"
#include "utility.h"
#include "vector/pool.h"

struct struct_Ast {
  Pool *symbols;
  Sexp *sexp;
};

static int pool_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Entry *l = lhs, *r = rhs;
  const Size lsz = l->size, rsz = r->size;
  int ret = utility_memcmp(l->buf, r->buf, lsz < rsz ? lsz : rsz);
  (void)extra;
  return 0 == ret ? lsz - rsz : ret;
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  Compare *cmp = compare_new(pool_compare);
  ast->symbols = pool_new(cmp);
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
  found = pool_find(ast->symbols, text, leng + 1);
  if (found) {
    Entry *entry = *found;
    return (const char *)entry->buf;
  } else {
    return pool_insert(ast->symbols, text, leng + 1);
  }
}
