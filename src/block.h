#ifndef INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B
#define INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B

#include "typedef.h"

Block *block_new(void);
void block_delete(Block *);
void block_insert(Block *, Instruction *);

#endif /* INCLUDE_GUARD_C5893AD5_9E36_4B47_A5BD_7EDC9894A05B */
