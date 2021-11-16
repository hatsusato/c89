#ifndef INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10
#define INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10

#include "map_type.h"
#include "util/type.h"

struct json;
struct json_obj;
struct json_pair;

struct json_obj *json_obj_new(void);
void json_obj_del(struct json *);
index_t json_obj_count(struct json *);
void json_obj_insert(struct json *, const char *, struct json *);
struct json *json_obj_get(struct json *, const char *);
bool_t json_obj_has(struct json *, const char *);
struct json_pair *json_obj_find(struct json *, const char *);
void json_obj_sort(struct json *);
void json_obj_foreach(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_ABC752EE_C142_4BE7_8DB6_61F2C2E61D10 */
