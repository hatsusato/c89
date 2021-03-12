#ifndef INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76
#define INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76

#include "compare/typedef.h"
#include "utility/types.h"

void insert_sort(CompareElem *, CompareElem *, Compare *);
void quick_sort(CompareElem *, CompareElem *, Compare *);
const CompareElem *binary_search(CompareElem, const CompareElem *,
                                 const CompareElem *, Compare *);

#endif /* INCLUDE_GUARD_0C8B0910_CE56_48A5_8BFB_257BD9BDAB76 */
