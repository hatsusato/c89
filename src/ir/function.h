#ifndef INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17
#define INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17

#include "json/map_type.h"

struct json;

void ir_function_init(struct json *);
void ir_function_finish(struct json *);
struct json *ir_function_new_block(struct json *);
struct json *ir_function_new_instr(struct json *, const char *);
struct json *ir_function_new_alloca(struct json *);
void ir_function_set_name(struct json *, struct json *);
const char *ir_function_get_name(struct json *);
void ir_function_foreach(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_A1347A49_DCBC_4F34_8469_952AF077EE17 */
