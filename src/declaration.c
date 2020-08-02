#include "declaration.h"

#include "function.h"
#include "utility.h"

struct struct_Declaration {
  DeclarationTag tag;
  void *data;
};

static Declaration *declaration_new(DeclarationTag tag) {
  Declaration *decl = UTILITY_MALLOC(Declaration);
  decl->tag = tag;
  decl->data = NULL;
  return decl;
}

Declaration *declaration_new_function(Function *func) {
  Declaration *decl = declaration_new(DECLARATION_FUNCTION);
  decl->data = func;
  return decl;
}
void declaration_delete(Declaration *decl) {
  assert(decl);
  function_delete(decl->data);
  UTILITY_FREE(decl);
}
