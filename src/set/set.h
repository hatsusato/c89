#ifndef INCLUDE_GUARD_9B4B925D_F58D_4277_B9FC_F12C65EFFC66
#define INCLUDE_GUARD_9B4B925D_F58D_4277_B9FC_F12C65EFFC66

#include "util/type.h"

struct set;

void set_init(struct set *, align_t, cmp_t);
void set_finish(struct set *);

#endif /* INCLUDE_GUARD_9B4B925D_F58D_4277_B9FC_F12C65EFFC66 */
