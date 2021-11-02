#ifndef INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10
#define INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10

#include "util/type.h"

struct json;
struct json_closure;
struct json_map;
struct json_obj;
struct json_pair;
struct json_printer;

struct json_obj *json_obj_new(void);
void json_obj_delete(struct json_obj *);
index_t json_obj_count(struct json_obj *);
void json_obj_insert(struct json_obj *, const char *, struct json *);
struct json *json_obj_get(struct json_obj *, const char *);
bool_t json_obj_has(struct json_obj *, const char *);
struct json_pair *json_obj_find(struct json_obj *, const char *);
void json_obj_sort(struct json_obj *);
void json_obj_foreach(struct json_obj *, struct json_map *);
void json_obj_map(struct json_obj *, struct json_closure *);
void json_obj_print(struct json_obj *, struct json_printer *);

#endif /* INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10 */
