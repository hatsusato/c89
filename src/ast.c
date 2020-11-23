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
const char *ast_show(AstTag tag) {
  const char *name[] = {"",
#define HANDLE(name, str) str,
#include "enum/keyword.def"
#
#include "enum/token.def"
#
#include "enum/symbol.def"
#
#include "enum/expression.def"
#
#include "enum/declaration.def"
#
#include "enum/statement.def"
#
#include "enum/definition.def"
#undef HANDLE
                        "tag-count"};
  if (AST_NULL < tag && tag < AST_TAG_COUNT) {
    return name[tag];
  }
  return NULL;
}
AstTag ast_tag(Sexp *ast) {
  if (sexp_is_number(ast)) {
    return sexp_get_number(ast);
  } else if (sexp_is_pair(ast)) {
    return ast_tag(sexp_car(ast));
  }
  return AST_NULL;
}
