#include "ast/tag.h"

#include "sexp.h"

const char *ast_show(AstTag tag) {
  const char *name[] = {"",
#define HANDLE(name, str) str,
#include "ast/tag.def"
#undef HANDLE
                        "tag-count"};
  if (AST_NULL < tag && tag < AST_TAG_COUNT) {
    return name[tag];
  }
  return NULL;
}
