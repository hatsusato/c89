#include "ir/instruction.h"

#include "ir/builder_impl.h"
#include "ir/value_kind.h"

void builder_instruction_ret(Builder *builder) {
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_RET);
  builder_stack_add(builder, first);
  builder_stack_register(builder);
}
void builder_instruction_br(Builder *builder) {
  Value *first = builder_stack_top(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_BR);
  builder_stack_add(builder, first);
  builder_stack_register(builder);
}
