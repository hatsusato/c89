#ifndef INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E
#define INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E

#include "typedef.h"
#include "types.h"

Str *str_new(const char *, int);
void str_delete(Str *);
Size str_length(const Str *s);
const char *str_begin(const Str *s);
const char *str_end(const Str *s);

#endif /* INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E */
