#include "ir/instruction.h"

#include <stdio.h>

#include "ir/block.h"
#include "ir/instruction_type.h"
#include "ir/register.h"
#include "ir/stack_impl.h"
#include "ir/value_kind.h"
#include "utility.h"
#include "vector.h"

struct struct_Instruction {
  ValueKind kind;
  int id;
  Register reg;
  Vector *vec;
  const void *value;
  InstructionKind ikind;
};

static void instruction_insert(Instruction *instr, Value *value) {
  vector_push(instr->vec, value);
}
static void instruction_insert_block(Instruction *instr, Block *block) {
  vector_push(instr->vec, block);
}

void stack_instruction_ret(Stack *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_RET);
  instruction_insert(instr, expr);
}
void stack_instruction_br(Stack *stack, Block *label) {
  assert(label);
  if (!stack_last_terminator(stack)) {
    Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR);
    instruction_insert_block(instr, label);
  }
}
void stack_instruction_br_cond(Stack *stack, Value *expr, Block *then_label,
                               Block *else_label) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_BR_COND);
  instruction_insert(instr, expr);
  instruction_insert_block(instr, then_label);
  instruction_insert_block(instr, else_label);
}
Instruction *stack_instruction_switch(Stack *stack, Value *expr) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SWITCH);
  instruction_insert(instr, expr);
  return instr;
}
void stack_instruction_switch_finish(Stack *stack, Instruction *instr) {
  Block *default_label = stack_get_next(stack, STACK_NEXT_DEFAULT);
  Block *break_label = stack_get_next(stack, STACK_NEXT_BREAK);
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  Block *next = break_label ? break_label : stack_new_block(stack);
  stack_instruction_br(stack, next);
  instruction_insert_block(instr, default_label ? default_label : next);
  instruction_insert_block(instr, switch_block);
  if (break_label || !default_label) {
    stack_jump_block(stack, next);
  }
}
void stack_instruction_switch_case(Stack *stack, Value *value, Block *label) {
  Block *switch_block = stack_get_next(stack, STACK_NEXT_SWITCH);
  block_insert_switch(switch_block, value, label);
}
Instruction *stack_instruction_add(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ADD);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return instr;
}
Instruction *stack_instruction_sub(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_SUB);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return instr;
}
Instruction *stack_instruction_alloca(Stack *stack, const char *symbol) {
  Instruction *instr = instruction_new(INSTRUCTION_ALLOCA);
  stack_alloca(stack, symbol, instr);
  return instr;
}
Instruction *stack_instruction_load(Stack *stack, Value *src) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_LOAD);
  instruction_insert(instr, src);
  return instr;
}
Instruction *stack_instruction_store(Stack *stack, Value *src, Value *dst) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_STORE);
  instruction_insert(instr, src);
  instruction_insert(instr, dst);
  return instr;
}
Instruction *stack_instruction_icmp_ne(Stack *stack, Value *lhs, Value *rhs) {
  Instruction *instr = stack_new_instruction(stack, INSTRUCTION_ICMP_NE);
  instruction_insert(instr, lhs);
  instruction_insert(instr, rhs);
  return instr;
}

Instruction *instruction_new(InstructionKind kind) {
  Instruction *instr = UTILITY_MALLOC(Instruction);
  instr->kind = VALUE_INSTRUCTION;
  instr->id = -1;
  register_init(&instr->reg);
  instr->vec = vector_new(NULL);
  instr->value = NULL;
  instr->ikind = kind;
  return instr;
}
void instruction_delete(Instruction *instr) {
  vector_delete(instr->vec);
  UTILITY_FREE(instr);
}
Bool instruction_is_terminator(Instruction *instr) {
  switch (instr->ikind) {
#define HANDLE_INSTRUCTION_KIND(k) \
  case k:                          \
    return true
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_RET);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_BR);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_BR_COND);
    HANDLE_INSTRUCTION_KIND(INSTRUCTION_SWITCH);
#undef HANDLE_INSTRUCTION_KIND
  default:
    return false;
  }
}
int instruction_set_id(Instruction *instr, int id) {
  if (!instruction_is_terminator(instr) && INSTRUCTION_STORE != instr->ikind) {
    instr->id = id++;
  }
  return id;
}
static void instruction_pretty_ret(Vector *vec) {
  if (vector_empty(vec)) {
    printf("ret void");
  } else {
    printf("ret i32 ");
    value_print(vector_at(vec, 0));
  }
}
static void instruction_pretty_br(Vector *vec) {
  printf("br label ");
  value_print(vector_at(vec, 0));
}
static void instruction_pretty_br_cond(Vector *vec) {
  printf("br i1 ");
  value_print(vector_at(vec, 0));
  printf(", label ");
  value_print(vector_at(vec, 1));
  printf(", label ");
  value_print(vector_at(vec, 2));
}
static void instruction_pretty_switch(Vector *vec) {
  printf("switch i32 ");
  value_print(vector_at(vec, 0));
  printf(", label ");
  value_print(vector_at(vec, 1));
  printf(" [\n");
  block_pretty_switch(vector_at(vec, 2));
  printf("  ]");
}
static void instruction_pretty_add(Vector *vec) {
  printf(" = add nsw i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
static void instruction_pretty_sub(Vector *vec) {
  printf(" = sub nsw i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
static void instruction_pretty_alloca(Vector *vec) {
  printf(" = alloca i32, align 4");
  UTILITY_UNUSED(vec);
}
static void instruction_pretty_load(Vector *vec) {
  printf(" = load i32, i32* ");
  value_print(vector_at(vec, 0));
  printf(", align 4");
}
static void instruction_pretty_store(Vector *vec) {
  printf("store i32 ");
  value_print(vector_at(vec, 0));
  printf(", i32* ");
  value_print(vector_at(vec, 1));
  printf(", align 4");
}
static void instruction_pretty_icmp_ne(Vector *vec) {
  printf(" = icmp ne i32 ");
  value_print(vector_at(vec, 0));
  printf(", ");
  value_print(vector_at(vec, 1));
}
void instruction_print(Instruction *instr) {
  printf("%%%d", instr->id);
}
void instruction_pretty(Instruction *instr) {
  Vector *vec = instr->vec;
  printf("  ");
  switch (instr->ikind) {
  case INSTRUCTION_RET:
    instruction_pretty_ret(vec);
    break;
  case INSTRUCTION_BR:
    instruction_pretty_br(vec);
    break;
  case INSTRUCTION_BR_COND:
    instruction_pretty_br_cond(vec);
    break;
  case INSTRUCTION_SWITCH:
    instruction_pretty_switch(vec);
    break;
  case INSTRUCTION_ADD:
    instruction_print(instr);
    instruction_pretty_add(vec);
    break;
  case INSTRUCTION_SUB:
    instruction_print(instr);
    instruction_pretty_sub(vec);
    break;
  case INSTRUCTION_ALLOCA:
    instruction_print(instr);
    instruction_pretty_alloca(vec);
    break;
  case INSTRUCTION_LOAD:
    instruction_print(instr);
    instruction_pretty_load(vec);
    break;
  case INSTRUCTION_STORE:
    instruction_pretty_store(vec);
    break;
  case INSTRUCTION_ICMP_NE:
    instruction_print(instr);
    instruction_pretty_icmp_ne(vec);
    break;
  default:
    assert(0);
    break;
  }
  printf("\n");
}
