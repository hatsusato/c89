#ifndef INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210
#define INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define UTILITY_SWAP(type, lhs, rhs) \
  do {                               \
    type tmp = (lhs);                \
    (lhs) = (rhs);                   \
    (rhs) = tmp;                     \
  } while (0);
#define UTILITY_MALLOC(type) (type *)malloc(sizeof(type))
#define UTILITY_MALLOC_ARRAY(type, count) (type *)malloc(sizeof(type) * (count))
#define UTILITY_FREE(var) \
  do {                    \
    free(var);            \
    (var) = NULL;         \
  } while (0)
#define UTILITY_MEMCPY(type, dst, src, count) \
  memcpy((dst), (src), sizeof(type) * (count))

#endif /* INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210 */
