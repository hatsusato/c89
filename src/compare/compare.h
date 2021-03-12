#ifndef INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57
#define INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57

#include "compare/typedef.h"
#include "utility/types.h"

Compare *compare_new(CompareCmp);
void compare_delete(Compare *);
CompareExtra compare_get_extra(Compare *);
void compare_set_extra(Compare *, CompareExtra);
int compare_cmp(Compare *, CompareElem, CompareElem);

#endif /* INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57 */
