#ifndef INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954
#define INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954

#include "compare/typedef.h"
#include "utility/types.h"
#include "vector/typedef.h"

Pool *pool_new(VectorDestructor, Compare *);
void pool_delete(Pool *);
void pool_clear(Pool *);
void pool_insert(Pool *, CompareElem);
const VectorElem *pool_find(Pool *, CompareElem);

#endif /* INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954 */
