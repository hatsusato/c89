#ifndef INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210
#define INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210

#include <assert.h>
#include <stddef.h>

typedef int Bool;
#define true (1)
#define false (0)
#define nil (NULL)

typedef unsigned char Byte;
typedef int Size;
typedef int Index;
typedef int Alignment;

#define SWAP(type, lhs, rhs) \
  do {                       \
    type tmp = lhs;          \
    lhs = rhs;               \
    rhs = tmp;               \
  } while (0);

#endif /* INCLUDE_GUARD_26FC0E3E_05C7_464D_8860_9F5E5E2F9210 */
