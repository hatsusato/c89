#include "ast.h"

const char* ast_show(int tag) {
  const char* name[] = {"tag-begin",
#define HANDLE(name, str) str,
#include "enum/keyword.def"
#
#include "enum/token.def"
#
#include "enum/expressions.def"
#undef HANDLE
                        "declaration",
                        "declaration-init",
                        "declaration-specifiers",
                        "init-declarator-list",
                        "init-declarator",
                        "type-name",
                        "tag-end"};
  return name[tag];
}
boolean ast_is_token(int tag) {
  switch (tag) {
#define HANDLE(name, str) case AST_##name:
#include "enum/token.def"
#undef HANDLE
    return true;
  default:
    return false;
  }
}
