#include "ast.h"

const char* ast_show(int tag) {
  const char* name[] = {"tag-begin", "nil",
#define HANDLE(name, str) str,
#include "enum/keyword.def"
#
#include "enum/token.def"
#
#include "enum/operator.def"
#
#include "enum/punctuator.def"
#
#include "enum/expression.def"
#
#include "enum/declaration.def"
#undef HANDLE
                        "tag-end"};
  return name[tag];
}
boolean ast_is_token(int tag) {
  switch (tag) {
#define HANDLE(name, str) case AST_##name:
#include "enum/keyword.def"
#include "enum/token.def"
#undef HANDLE
    return true;
  default:
    return false;
  }
}
