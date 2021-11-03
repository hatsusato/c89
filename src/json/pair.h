#ifndef INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638
#define INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638

#include "util/type.h"

struct json;
struct json_pair;

const char *json_pair_key(const struct json_pair *);
struct json *json_pair_val(const struct json_pair *);
void json_pair_set(struct json_pair *, const char *, struct json *);
struct json_pair *json_pair_search(struct json_pair *, index_t, const char *);

#endif /* INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638 */
