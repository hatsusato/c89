#include "ir/instruction.h"

#include "ir/builder_impl.h"
#include "ir/value_kind.h"

static void builder_instruction_unary(Builder *builder, ValueKind kind,
                                      Value *first) {
  builder_stack_new_value(builder, kind);
  builder_stack_add(builder, first);
  builder_stack_register(builder);
}

void builder_instruction_ret(Builder *builder) {
  Value *first = builder_stack_pop(builder);
  builder_instruction_unary(builder, VALUE_INSTRUCTION_RET, first);
}
void builder_instruction_br(Builder *builder) {
  Value *first = builder_stack_top(builder);
  builder_instruction_unary(builder, VALUE_INSTRUCTION_BR, first);
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
void builder_instruction_add(Builder *builder) {
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_ADD);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_register(builder);
}
void builder_instruction_alloca(Builder *builder, const char *symbol) {
  builder_stack_new_value(builder, VALUE_INSTRUCTION_ALLOCA);
  builder_stack_insert_symbol(builder, symbol);
  builder_stack_register(builder);
}
void builder_instruction_load(Builder *builder) {
  Value *first = builder_stack_pop(builder);
  builder_instruction_unary(builder, VALUE_INSTRUCTION_LOAD, first);
}
void builder_instruction_store(Builder *builder) {
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_STORE);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_register(builder);
}
void builder_instruction_icmp_ne(Builder *builder) {
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, VALUE_INSTRUCTION_ICMP_NE);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_register(builder);
}
