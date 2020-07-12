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

Bool utility_str_eq(const char*, const char*);

#endif /* INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210 */
