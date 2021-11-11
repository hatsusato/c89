#ifndef INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08
#define INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08

#include "json/map_type.h"

struct json;

void ir_module_init(struct json *);
void ir_module_finish(struct json *);
struct json *ir_module_new_function(struct json *);
struct json *ir_module_make_global(struct json *, struct json *);
void ir_module_foreach(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_6DEB3F5D_8CE8_4C31_B2A0_7C9C1EFC5B08 */
