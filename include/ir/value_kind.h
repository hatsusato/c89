#ifndef INCLUDE_GUARD_53C6EB3B_EBA5_4347_9FC7_1275783E0C89
#define INCLUDE_GUARD_53C6EB3B_EBA5_4347_9FC7_1275783E0C89

typedef enum {
  VALUE_FUNCTION,
  VALUE_BLOCK,
  VALUE_INTEGER_CONSTANT,
  VALUE_INSTRUCTION_RET,
  VALUE_INSTRUCTION_ADD,
  VALUE_INSTRUCTION_ALLOCA,
  VALUE_INSTRUCTION_LOAD,
  VALUE_INSTRUCTION_STORE,
  VALUE_KIND_END
} ValueKind;

#endif /* INCLUDE_GUARD_53C6EB3B_EBA5_4347_9FC7_1275783E0C89 */
