#include "ast.h"

const char* ast_show(int tag) {
  const char* name[] = {"nil",
                        "identifier",
                        "constant",
                        "floating-constant",
                        "integer-constant",
                        "enumeration-constant",
                        "character-constant",
                        "string-literal",
#define HANDLE(name, str) str,
#include "enum/expressions.def"
#undef HANDLE
                        "declaration",
                        "declaration-init",
                        "declaration-specifiers",
                        "init-declarator-list",
                        "init-declarator",
                        "type-name"};
  return name[tag];
}
boolean ast_is_token(int tag) {
  switch (tag) {
  case AST_IDENTIFIER:
  case AST_CONSTANT:
  case AST_FLOATING_CONSTANT:
  case AST_INTEGER_CONSTANT:
  case AST_ENUMERATION_CONSTANT:
  case AST_CHARACTER_CONSTANT:
  case AST_STRING_LITERAL:
    return true;
  default:
    return false;
  }
}
