#ifndef INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57
#define INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57

#include "compare/typedef.h"
#include "utility/types.h"
#include "vector/typedef.h"

Compare *compare_new(CompareCmp, CompareExtra);
Compare *compare_new_for_vector(VectorCmp);
void compare_delete(Compare *);
int compare_cmp(Compare *, CompareElem, CompareElem);
void compare_sort_quick(Compare *, CompareElem *, CompareElem *);
CompareElem compare_binary_search(Compare *, CompareElem, const CompareElem *,
                                  const CompareElem *);

#endif /* INCLUDE_GUARD_34AB7F3A_885A_4F62_9026_BA9D1D12BD57 */
