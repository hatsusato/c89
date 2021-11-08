#ifndef INCLUDE_GUARD_4E7CB2CB_243B_42B7_8120_E8AE57FD19D2
#define INCLUDE_GUARD_4E7CB2CB_243B_42B7_8120_E8AE57FD19D2

#include "util/type.h"

#define SYMBOL_IMMEDIATE "immediate"

struct json;

void convert_immediate(struct json *);
bool_t convert_immediate_additive_expression(struct json *, struct json *,
                                             struct json *);

#endif /* INCLUDE_GUARD_4E7CB2CB_243B_42B7_8120_E8AE57FD19D2 */
