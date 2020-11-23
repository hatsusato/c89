#include "ast/ast_tag.h"

#include "sexp.h"

const char *ast_show(AstTag tag) {
  const char *name[] = {"",
#define HANDLE(name, str) str,
#include "ast/keyword.def"
#
#include "ast/token.def"
#
#include "ast/symbol.def"
#
#include "ast/expression.def"
#
#include "ast/declaration.def"
#
#include "ast/statement.def"
#
#include "ast/definition.def"
#undef HANDLE
                        "tag-count"};
  if (AST_NULL < tag && tag < AST_TAG_COUNT) {
    return name[tag];
  }
  return NULL;
}
