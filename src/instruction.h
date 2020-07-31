#ifndef INCLUDE_GUARD_B22CD5CF_CFA4_4141_958E_3B8F73C9A6F1
#define INCLUDE_GUARD_B22CD5CF_CFA4_4141_958E_3B8F73C9A6F1

#include "typedef.h"

typedef enum {
  INSTRUCTION_ALLOC,
  INSTRUCTION_STORE,
  INSTRUCTION_RET
} InstructionTag;

Instruction *instruction_new(InstructionTag);
void instruction_delete(Instruction *);
void instruction_insert_register(Instruction *, Instruction *);
void instruction_insert_integer(Instruction *, int);

#endif /* INCLUDE_GUARD_B22CD5CF_CFA4_4141_958E_3B8F73C9A6F1 */
