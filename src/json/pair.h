#ifndef INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638
#define INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638

struct json;
struct json_pair;

const char *json_pair_key(const struct json_pair *);
struct json *json_pair_val(const struct json_pair *);
void json_pair_set(struct json_pair *, const char *, struct json *);

#endif /* INCLUDE_GUARD_38C6CC58_0DA0_4BFD_942B_16D00E174638 */
