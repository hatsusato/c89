#include "ast.h"

#include <assert.h>

const char *ast_show(int tag) {
  const char *name[] = {"tag-begin",
#define HANDLE(name, str) str,
#include "enum/misc.def"
#
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
                        "tag-end"};
  assert(AST_TAG_BEGIN < tag && tag < AST_TAG_END);
  return name[tag];
}
