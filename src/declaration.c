#include "declaration.h"

#include "utility.h"

struct struct_Declaration {
  DeclarationTag tag;
};

static Declaration *declaration_new(DeclarationTag tag) {
  Declaration *decl = UTILITY_MALLOC(Declaration);
  decl->tag = tag;
  return decl;
}

void declaration_delete(Declaration *decl) {
  UTILITY_FREE(decl);
}
