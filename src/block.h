#ifndef INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B
#define INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B

#include <stdio.h>

#include "instruction.h"
#include "typedef.h"

Block *block_new(void);
void block_delete(Block *);
Instruction *block_new_instruction(Block *, InstructionTag);
void block_print(FILE *, Block *);

#endif /* INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B */
