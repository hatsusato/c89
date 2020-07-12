#ifndef INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210
#define INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210

#include <assert.h>

#include "typedef.h"

#define SWAP(type, lhs, rhs) \
  do {                       \
    type tmp = lhs;          \
    lhs = rhs;               \
    rhs = tmp;               \
  } while (0);
#define UTILITY_MALLOC(type) (type*)utility_malloc(sizeof(type))
#define UTILITY_MALLOC_ARRAY(type, count) \
  (type*)utility_malloc(sizeof(type) * count)
#define UTILITY_FREE(var) \
  do {                    \
    utility_free(var);    \
    var = NULL;           \
  } while (0)
#define UTILITY_MEMCPY(type, dst, src, count) \
  utility_memcpy(dst, src, sizeof(type) * count)

Bool utility_str_eq(const char*, const char*);
void* utility_malloc(size_t);
void utility_free(void*);
void utility_memcpy(void* dst, const void* src, size_t count);

#endif /* INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210 */
