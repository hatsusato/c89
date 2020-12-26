#ifndef INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76
#define INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76

#include "compare/types.h"
#include "utility/types.h"

void insert_sort(ElemType *, ElemType *, Compare *);
void quick_sort(ElemType *, ElemType *, Compare *);
const ElemType *binary_search(ElemType, const ElemType *, const ElemType *,
                              Compare *);

#endif /* INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76 */
