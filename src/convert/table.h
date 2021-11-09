#ifndef INCLUDE_GUARD_58EA80CA_1E03_4C77_8886_716DB4E8128C
#define INCLUDE_GUARD_58EA80CA_1E03_4C77_8886_716DB4E8128C

#include "util/type.h"

struct json;

void convert_table_insert(struct json *, struct json *, struct json *);
struct json *convert_table_lookup(struct json *, struct json *);
void convert_table_push(struct json *);
void convert_table_pop(struct json *);
bool_t convert_table_is_global(struct json *);

#endif /* INCLUDE_GUARD_58EA80CA_1E03_4C77_8886_716DB4E8128C */
