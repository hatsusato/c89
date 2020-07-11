#ifndef INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E
#define INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E

#include "typedef.h"
#include "utility.h"

String *string_new(const char *);
String *string_new_s(const char *, int);
void string_delete(String *);
Size string_length(String *s);
char *string_begin(String *s);
char *string_end(String *s);

#endif /* INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E */
