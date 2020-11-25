#ifndef INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210
#define INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210

#include <assert.h>

#include "types.h"

#define UTILITY_SWAP(type, lhs, rhs) \
  do {                               \
    type tmp = (lhs);                \
    (lhs) = (rhs);                   \
    (rhs) = tmp;                     \
  } while (0);
#define UTILITY_MALLOC(type) (type *)utility_malloc(sizeof(type))
#define UTILITY_MALLOC_ARRAY(type, count) \
  (type *)utility_malloc(sizeof(type) * (count))
#define UTILITY_FREE(var) utility_free((ElemType)(var))
#define UTILITY_MEMCPY(type, dst, src, count) \
  utility_memcpy((void *)(dst), (src), sizeof(type) * (count))

ElemType utility_malloc(size_t);
void utility_free(ElemType);
void utility_memcpy(void *, const void *, size_t);
int utility_memcmp(const void *, const void *, size_t);
int utility_strcmp(const char *, const char *);

#endif /* INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210 */
