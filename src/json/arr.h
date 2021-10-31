#ifndef INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526
#define INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526

#include "util/type.h"

struct json;
struct json_arr;

struct json_arr *json_arr_new(void);
void json_arr_delete(struct json_arr *);
index_t json_arr_count(struct json_arr *);
struct json *json_arr_at(struct json_arr *, index_t);
void json_arr_push(struct json_arr *, struct json *);

#endif /* INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526 */
