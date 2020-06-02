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
                        "primary-expression",
                        "postfix-expression",
                        "postfix-operator",
                        "postfix-array",
                        "postfix-call",
                        "postfix-call-args",
                        "postfix-member",
                        "postfix-arrow",
                        "postfix-incr",
                        "postfix-decr",
                        "argument-expression-list",
                        "unary-expression",
                        "unary-operator",
                        "unary-incr",
                        "unary-decr",
                        "unary-amper",
                        "unary-aster",
                        "unary-plus",
                        "unary-minus",
                        "unary-tilde",
                        "unary-excl",
                        "unary-sizeof",
                        "unary-sizeof-type",
                        "cast-expression",
                        "multiplicative-expression",
                        "multiplicative-operator",
                        "multiplicative-aster",
                        "multiplicative-slash",
                        "multiplicative-perc",
                        "additive-expression",
                        "additive-operator",
                        "additive-plus",
                        "additive-minus",
                        "shift-expression",
                        "shift-operator",
                        "relational-expression",
                        "relational-operator",
                        "equality-expression",
                        "equality-operator",
                        "and-expression",
                        "exclusive-or-expression",
                        "inclusive-or-expression",
                        "logical-and-expression",
                        "logical-or-expression",
                        "conditional-expression",
                        "assignment-expression",
                        "assignment-operator",
                        "expression",
                        "constant-expression",
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
