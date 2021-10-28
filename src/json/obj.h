#ifndef INCLUDE_GUARD_1A3501D5_6CCC_4A43_9369_088AA3991F18
#define INCLUDE_GUARD_1A3501D5_6CCC_4A43_9369_088AA3991F18

struct json *json_obj_new(void);
void json_obj_delete(struct json *);
void json_obj_insert(struct json *, const char *, struct json *);
struct json *json_obj_at(struct json *, const char *);

#endif /* INCLUDE_GUARD_1A3501D5_6CCC_4A43_9369_088AA3991F18 */
