#ifndef INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954
#define INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954

#include "compare/types.h"
#include "pool/types.h"
#include "utility/types.h"

Pool *pool_new(Destructor, Compare *);
void pool_delete(Pool *);

#endif /* INCLUDE_GUARD_E5CBD615_F933_4AAA_8E0A_D8BDF23D4954 */
