#ifndef INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551
#define INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551

#include "util/type.h"

struct json;
struct json_arr;
struct json_int;
struct json_obj;
struct json_str;

void json_del(struct json *);
void json_ref(struct json *);
struct json *json_null(void);
struct json *json_new_int(int);
struct json *json_new_str(const char *);
struct json *json_new_arr(void);
struct json *json_new_obj(void);
struct json *json_new_weak(struct json *);
bool_t json_is_null(struct json *);
bool_t json_is_int(struct json *);
bool_t json_is_str(struct json *);
bool_t json_is_arr(struct json *);
bool_t json_is_obj(struct json *);
bool_t json_is_weak(struct json *);
struct json_int *json_as_int(struct json *);
struct json_str *json_as_str(struct json *);
struct json_arr *json_as_arr(struct json *);
struct json_obj *json_as_obj(struct json *);
struct json *json_unwrap(struct json *);

#endif /* INCLUDE_GUARD_ECF85374_1D53_4EC2_A2A3_98ADD3780551 */
