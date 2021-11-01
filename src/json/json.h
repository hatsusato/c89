#ifndef INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E
#define INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E

#include "util/type.h"

struct json;
struct json_arr;
struct json_obj;
struct json_str;

typedef void (*json_map_t)(const char *, struct json *, void *);

struct json_map {
  json_map_t map;
  void *extra;
};

struct json *json_null(void);
bool_t json_is_null(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);
index_t json_count(struct json *);
struct json_str *json_as_str(struct json *);
struct json_arr *json_as_arr(struct json *);
struct json_obj *json_as_obj(struct json *);
void json_print(struct json *);

#include "json/arr.h"
#include "json/obj.h"
#include "json/str.h"

#endif /* INCLUDE_GUARD_5E299705_D2B2_4EFA_AD2B_575DB876526E */
