#include "spec.h"

#include "ir/module.h"
#include "ir/type/struct.h"
#include "utility/utility.h"

struct struct_TypeSpec {
  Bool spec[TYPE_SPEC_COUNT];
};

static Bool type_spec_get(TypeSpec *spec, TypeSpecIndex i) {
  return spec->spec[i];
}

TypeSpec *type_spec_new(void) {
  TypeSpec *spec = UTILITY_MALLOC(TypeSpec);
  type_spec_reset(spec);
  return spec;
}
void type_spec_delete(TypeSpec *spec) {
  UTILITY_FREE(spec);
}
void type_spec_set(TypeSpec *spec, TypeSpecIndex i) {
  spec->spec[i] = true;
}
void type_spec_reset(TypeSpec *spec) {
  TypeSpecIndex i = 0;
  for (; i < TYPE_SPEC_COUNT; ++i) {
    spec->spec[i] = false;
  }
}
void type_init_spec(Type *type, TypeSpec *spec) {
  if (type_spec_get(spec, TYPE_SPEC_FLOAT)) {
    UTILITY_ASSERT(0);
  } else if (type_spec_get(spec, TYPE_SPEC_DOUBLE)) {
    UTILITY_ASSERT(0);
  } else {
    type->kind = TYPE_INTEGER;
    if (type_spec_get(spec, TYPE_SPEC_VOID)) {
      type->data.size = 0;
    } else if (type_spec_get(spec, TYPE_SPEC_CHAR)) {
      type->data.size = 8;
    } else if (type_spec_get(spec, TYPE_SPEC_SHORT)) {
      type->data.size = 16;
    } else if (type_spec_get(spec, TYPE_SPEC_LONG)) {
      type->data.size = 64;
    } else {
      type->data.size = 32;
    }
  }
}
Type *type_new_from_spec(Module *module, TypeSpec *spec) {
  Type type;
  type_init_spec(&type, spec);
  return module_new_type(module, &type);
}
