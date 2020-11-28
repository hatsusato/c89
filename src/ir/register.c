#include "ir/register.h"

#include "ir/register_type.h"
#include "utility.h"

struct struct_RegisterGenerator {
  int last;
};

RegisterGenerator *register_generator_new(void) {
  RegisterGenerator *gen = UTILITY_MALLOC(RegisterGenerator);
  gen->last = 0;
  return gen;
}
void register_generator_delete(RegisterGenerator *gen) {
  UTILITY_FREE(gen);
}
