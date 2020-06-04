#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

#include "utility.h"

enum AstTag {
  AST_TAG_BEGIN,
#define HANDLE(name, str) AST_##name,
#include "enum/keyword.def"
#
#include "enum/token.def"
#
#include "enum/expressions.def"
#undef HANDLE
  AST_DECLARATION,
  AST_DECLARATION_INIT,
  AST_DECLARATION_SPECIFIERS,
  AST_INIT_DECLARATOR_LIST,
  AST_INIT_DECLARATOR,
  AST_TYPE_NAME,
  AST_TAG_END
};

const char* ast_show(int);
boolean ast_is_token(int);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
