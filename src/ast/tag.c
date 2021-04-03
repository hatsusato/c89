#include "ast/tag.h"

#include "sexp/sexp.h"

const char *ast_show(SyntaxTag tag) {
  const char *name[] = {
#define HANDLE(name, str) str,
#include "ast/tag.def"
#undef HANDLE
      "tag-count"};
  if (SYNTAX_NULL < tag && tag < SYNTAX_TAG_COUNT) {
    return name[tag];
  }
  return NULL;
}
