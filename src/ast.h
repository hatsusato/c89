#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

#include "utility.h"

enum AstTag {
  AST_TAG_BEGIN,
  AST_NIL,
  AST_ARRAY,
  AST_CALL,
#define HANDLE(name, str) AST_##name,
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
  AST_TAG_END
};

const char *ast_show(int);
boolean ast_is_token(int);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
