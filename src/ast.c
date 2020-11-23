#include "ast.h"

#include "set.h"
#include "sexp.h"
#include "utility.h"

struct struct_Ast {
  Set *symbols;
  Sexp *sexp;
};

static const char *symbols_construct(const char *text, Size size) {
  char *buf = UTILITY_MALLOC_ARRAY(char, size + 1);
  UTILITY_MEMCPY(char, buf, text, size);
  buf[size] = '\0';
  assert(text[size] == 0);
  return buf;
}
static void symbols_destruct(ElemType elem) {
  UTILITY_FREE(elem);
}
static int symbols_strcmp(const ElemType *lhs, const ElemType *rhs) {
  return strcmp(*lhs, *rhs);
}

Ast *ast_new(void) {
  Ast *ast = UTILITY_MALLOC(Ast);
  ast->symbols = set_new(symbols_destruct, symbols_strcmp);
  ast->sexp = sexp_nil();
  return ast;
}
void ast_delete(Ast *ast) {
  sexp_delete(ast->sexp);
  set_delete(ast->symbols);
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
  const char *symbol = symbols_construct(text, leng);
  return set_insert(ast->symbols, (ElemType)symbol);
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
