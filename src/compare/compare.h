#ifndef INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57
#define INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57

#include "compare/types.h"

Compare *compare_new(Cmp);
void compare_delete(Compare *);
Compare *compare_new_strcmp(void);
CompareExtra compare_get_extra(Compare *);
void compare_set_extra(Compare *, CompareExtra, Destructor);
int compare_cmp(Compare *, ElemType, ElemType);

#endif /* INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57 */
