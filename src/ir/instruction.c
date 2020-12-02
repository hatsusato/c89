#include "ir/instruction.h"

#include "ir/builder_impl.h"
#include "ir/value_kind.h"

static void builder_instruction_unary(Builder *builder, ValueKind kind) {
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, kind);
  builder_stack_add(builder, first);
  builder_stack_register(builder);
}
static void builder_instruction_binary(Builder *builder, ValueKind kind) {
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, kind);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_register(builder);
}
static void builder_instruction_ternary(Builder *builder, ValueKind kind) {
  Value *third = builder_stack_pop(builder);
  Value *second = builder_stack_pop(builder);
  Value *first = builder_stack_pop(builder);
  builder_stack_new_value(builder, kind);
  builder_stack_add(builder, first);
  builder_stack_add(builder, second);
  builder_stack_add(builder, third);
  builder_stack_register(builder);
}

void builder_instruction_ret(Builder *builder) {
  builder_instruction_unary(builder, VALUE_INSTRUCTION_RET);
}
void builder_instruction_br(Builder *builder) {
  builder_instruction_unary(builder, VALUE_INSTRUCTION_BR);
}
void builder_instruction_br_cond(Builder *builder) {
  builder_instruction_ternary(builder, VALUE_INSTRUCTION_BR_COND);
}
void builder_instruction_add(Builder *builder) {
  builder_instruction_binary(builder, VALUE_INSTRUCTION_ADD);
}
void builder_instruction_alloca(Builder *builder, const char *symbol) {
  builder_stack_new_value(builder, VALUE_INSTRUCTION_ALLOCA);
  builder_stack_insert_symbol(builder, symbol);
  builder_stack_register(builder);
}
void builder_instruction_load(Builder *builder) {
  builder_instruction_unary(builder, VALUE_INSTRUCTION_LOAD);
}
void builder_instruction_store(Builder *builder) {
  builder_instruction_binary(builder, VALUE_INSTRUCTION_STORE);
}
void builder_instruction_icmp_ne(Builder *builder) {
  builder_instruction_binary(builder, VALUE_INSTRUCTION_ICMP_NE);
}
