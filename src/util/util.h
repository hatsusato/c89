#ifndef INCLUDE_GUARD_9F0D8DB1_8A8A_4615_9EB1_EF81E4748100
#define INCLUDE_GUARD_9F0D8DB1_8A8A_4615_9EB1_EF81E4748100

#include <assert.h>

#include "type.h"

#define UTIL_UNUSED(var) ((void)var)
#define UTIL_MAX(lhs, rhs) (((lhs) < (rhs)) ? (rhs) : (lhs))
#define UTIL_MIN(lhs, rhs) (((lhs) < (rhs)) ? (lhs) : (rhs))
#define UTIL_BOOL(expr) ((expr) ? true : false)
#define UTIL_SWAP(type, lhs, rhs)                                  \
  do {                                                             \
    byte_t buf_28321f6d_b6bb_4bf6_bcf2_b1744cfbc621[sizeof(type)]; \
    util_swap_impl(sizeof(type), (lhs), (rhs),                     \
                   buf_28321f6d_b6bb_4bf6_bcf2_b1744cfbc621);      \
  } while (false)

void *util_malloc(align_t);
void *util_malloc_array(index_t, align_t);
void util_free(void *);
void util_swap_impl(size_t, void *, void *, void *);
void util_memcpy(void *, const void *, index_t, align_t);
int util_strcmp(const char *, const char *);
bool_t util_streq(const char *, const char *);
const char *util_strdup(const char *);
int util_atoi(const char *);
void util_print(const char *, ...);
void util_error(const char *, ...);

#endif /* INCLUDE_GUARD_9F0D8DB1_8A8A_4615_9EB1_EF81E4748100 */
