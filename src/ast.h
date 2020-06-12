#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

enum AstTag {
  AST_TAG_BEGIN,
#define HANDLE(name, str) AST_##name,
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
  AST_TAG_END
};

const char *ast_show(int);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
