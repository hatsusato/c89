#include "utility.h"

#include <string.h>

Bool utility_str_eq(const char* lhs, const char* rhs) {
  return 0 == strcmp(lhs, rhs);
}