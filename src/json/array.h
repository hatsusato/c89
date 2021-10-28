#ifndef INCLUDE_GUARD_CDB9EC8A_96C8_4113_8118_8E0D2E8316D8
#define INCLUDE_GUARD_CDB9EC8A_96C8_4113_8118_8E0D2E8316D8

#include "util/type.h"

struct json_pair;
struct json_array;

void json_array_insert(struct json_array *, struct json_pair *, index_t);
void json_array_resize(struct json_array *, index_t);
void json_array_sort(struct json_array *, cmp_t);
struct json_pair *json_array_search(struct json_array *, struct json_pair *,
                                    cmp_t);

#endif /* INCLUDE_GUARD_CDB9EC8A_96C8_4113_8118_8E0D2E8316D8 */
