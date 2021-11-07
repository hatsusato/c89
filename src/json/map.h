#ifndef INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284
#define INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284

#include "map_type.h"
#include "util/type.h"

struct json;
struct json_vec;

void *json_map_extra(struct json_map *);
void json_map_finish(struct json_map *);
index_t json_map_index(struct json_map *);
const char *json_map_key(struct json_map *);
struct json *json_map_val(struct json_map *);
void json_map_foreach(json_map_t, void *, struct json_vec *);
void json_foreach(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284 */
