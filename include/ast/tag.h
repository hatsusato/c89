#ifndef INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1
#define INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1

typedef enum {
  AST_NULL,
#define HANDLE(name, str) name,
#include "ast/tag.def"
#undef HANDLE
  AST_TAG_COUNT
} AstTag;

const char *ast_show(AstTag);

#endif /* INCLUDE_GUARD_35338543_3CA8_4BC0_811F_5E8A24EDBED1 */
