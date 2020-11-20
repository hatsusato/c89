#ifndef INCLUDE_GUARD_7858FB03_AA4D_4F96_8662_555961A8FF17
#define INCLUDE_GUARD_7858FB03_AA4D_4F96_8662_555961A8FF17

#include "typedef.h"

typedef enum { VALUE_REGISTER, VALUE_INTEGER } ValueTag;

Value *value_new_register(Instruction *);
Value *value_new_integer(int);
void value_delete(Value *);

#endif /* INCLUDE_GUARD_7858FB03_AA4D_4F96_8662_555961A8FF17 */
