#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "utility.h"

struct struct_Set;
typedef struct struct_Set Set;

Set *set_new(void);
void set_delete(Set *);
Bool set_string_contains(const Set *, const char *);
void set_string_insert(Set *, const char *);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
