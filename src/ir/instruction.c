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
void builder_instruction_br_cond(Builder *builder) {
  Value *third = builder_stack_pop(builder);
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_BR_COND);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_add(builder, third);
  builder_stack_register(builder);
  builder_stack_push(builder, second);
  builder_stack_push(builder, third);
}
