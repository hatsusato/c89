#ifndef INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9
#define INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9

struct json;
struct json_factory;
struct pool;

struct json_factory *json_factory_new(struct pool *);
void json_factory_delete(struct json_factory *);
struct json *json_factory_null(struct json_factory *);
struct json *json_factory_str(struct json_factory *, const char *);
struct json *json_factory_arr(struct json_factory *);
struct json *json_factory_obj(struct json_factory *);

#endif /* INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9 */
