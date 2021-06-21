#ifndef INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1
#define INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1

typedef enum {
#define HANDLE(name, str) name,
#include "ast/tag.def"
#undef HANDLE
  SYNTAX_TAG_COUNT
} SyntaxTag;

const char *ast_show(SyntaxTag);

#endif /* INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1 */
