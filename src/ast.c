#include "ast.h"

#include "utility.h"

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
                        "unknown", "tag-end"};
  assert(AST_TAG_BEGIN < tag && tag < AST_TAG_END);
  return name[tag];
}
int ast_to_int(const char *tag) {
  if (utility_str_eq(tag, "unknown")) {
    return AST_UNKNOWN;
  }
#define HANDLE(name, str)              \
  else if (utility_str_eq(tag, str)) { \
    return AST_##name;                 \
  }
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
  else {
    return AST_UNKNOWN;
  }
}
