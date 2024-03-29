#ifndef INCLUDE_GUARD_0363FDA6_C88C_4B43_9B75_218C62E9A789
#define INCLUDE_GUARD_0363FDA6_C88C_4B43_9B75_218C62E9A789

#include "map_type.h"
#include "util/type.h"

struct json;

void json_print(struct json *);
void json_insert_str(struct json *, const char *, const char *);
bool_t json_has(struct json *, const char *);
struct json *json_find(struct json *, const char *);
const char *json_get_str(struct json *);
struct json *json_find_identifier(struct json *);
void json_arr_append(struct json *, struct json *);
void json_obj_merge(struct json *, struct json *);
struct json *json_take(struct json *, const char *);

#endif /* INCLUDE_GUARD_0363FDA6_C88C_4B43_9B75_218C62E9A789 */
