#ifndef INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5
#define INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5

typedef enum {
  AST_TAG_BEGIN,
#define HANDLE(name, str) AST_##name,
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
  AST_UNKNOWN,
  AST_TAG_END
} AstTag;

const char *ast_show(AstTag);
int ast_to_int(const char *);

#endif /* INCLUDE_GUARD_A84E9F8A_C152_4807_9181_80EE16B4DFA5 */
