#include "ir/register.h"

#include "utility.h"

struct struct_Register {
  int id;
};

Register *register_new(void) {
  Register *reg = UTILITY_MALLOC(Register);
  reg->id = 0;
  return reg;
}
void register_set_id(Register *reg, int id) {
  reg->id = id;
}
