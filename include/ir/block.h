#ifndef INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195
#define INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195

#include "ir/block_type.h"
#include "ir/value_type.h"
#include "types.h"

Block *block_new(void);
void block_delete(Block *);
void block_insert(Block *, Value *);
void block_append(Block *, Block *);
Bool block_empty(Block *);
Bool block_is_terminated(Block *);

#endif /* INCLUDE_GUARD_158B0FE3_07C7_4187_B41D_C9D59FB58195 */
