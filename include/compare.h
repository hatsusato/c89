#ifndef INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57
#define INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57

#include "compare_type.h"
#include "types.h"

typedef const void *CompareExtra;
typedef int (*Cmp)(ElemType, ElemType, CompareExtra);

Compare *compare_new(Cmp);
void compare_delete(Compare *);
CompareExtra compare_set_extra(Compare *, CompareExtra);
int compare_cmp(Compare *, ElemType, ElemType);

#endif /* INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57 */
