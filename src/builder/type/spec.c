#include "spec.h"

#include "utility.h"

struct struct_TypeSpec {
  Bool spec[TYPE_SPEC_COUNT];
};

TypeSpec *type_spec_new(void) {
  TypeSpec *spec = UTILITY_MALLOC(TypeSpec);
  type_spec_reset(spec);
  return spec;
}
void type_spec_delete(TypeSpec *spec) {
  UTILITY_FREE(spec);
}
Bool type_spec_get(TypeSpec *spec, TypeSpecIndex i) {
  return spec->spec[i];
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
