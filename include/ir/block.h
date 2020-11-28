#ifndef INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1
#define INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1

#include "ir/block_type.h"
#include "ir/value_type.h"

Value *block_new(void);
void block_delete(Value *);
void block_insert(Value *, Value *);
void block_print(Value *);

#endif /* INCLUDE_GUARD_99995B0B_7C53_460D_87DC_0574B8F3FBB1 */
