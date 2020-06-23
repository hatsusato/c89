#ifndef INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E
#define INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E

#include "utility.h"

struct struct_String;
typedef struct struct_String String;

String* string_new(const char*);
void string_delete(String*);
Size string_length(String* s);
char* string_begin(String* s);
char* string_end(String* s);

#endif /* INCLUDE_GUARD_08E41EF5_65A1_4E4C_9B5A_FE5896BDA20E */
