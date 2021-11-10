#ifndef INCLUDE_GUARD_1E89582D_FC82_4187_9C45_D63C06551A2E
#define INCLUDE_GUARD_1E89582D_FC82_4187_9C45_D63C06551A2E

#include "json/map_type.h"

struct json;

struct json *ir_block_new(void);
void ir_block_foreach(struct json *, json_map_t, void *);

#endif /* INCLUDE_GUARD_1E89582D_FC82_4187_9C45_D63C06551A2E */
