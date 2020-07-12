#ifndef INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E
#define INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E

#include "typedef.h"

String *string_new(const char *, int);
void string_delete(String *);
Size string_length(const String *s);
const char *string_begin(const String *s);
const char *string_end(const String *s);

#endif /* INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E */
