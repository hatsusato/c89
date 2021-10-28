#ifndef INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9
#define INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9

struct json_factory;
struct pool;

struct json_factory *json_factory_new(struct pool *);
void json_factory_delete(struct json_factory *);

#endif /* INCLUDE_GUARD_E1A79B98_69B9_4F2F_BA13_B1D99BCE19C9 */
