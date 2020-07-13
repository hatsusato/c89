#ifndef INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E
#define INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E

#include "typedef.h"

Str *string_new(const char *, int);
void string_delete(Str *);
Size string_length(const Str *s);
const char *string_begin(const Str *s);
const char *string_end(const Str *s);

#endif /* INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E */
