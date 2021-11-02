#ifndef INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526
#define INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526

#include "util/type.h"

struct json;
struct json_callback;
struct json_arr;
struct json_map;
struct json_printer;

struct json_arr *json_arr_new(void);
void json_arr_delete(struct json_arr *);
index_t json_arr_count(struct json_arr *);
struct json *json_arr_at(struct json_arr *, index_t);
void json_arr_push(struct json_arr *, struct json *);
void json_arr_foreach(struct json_arr *, struct json_map *);
void json_arr_map(struct json_arr *, struct json_callback *);
void json_arr_print(struct json_arr *, struct json_printer *);

#endif /* INCLUDE_GUARD_5A572308_20F6_491E_A3CD_83B5A0D2B526 */
