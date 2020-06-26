#ifndef INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A
#define INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A

#include "utility.h"

struct struct_Set;
typedef struct struct_Set Set;

Set *set_new(void);
void set_delete(Set *set);
boolean set_string_contains(const Set *set, const char *str);

#endif /* INCLUDE_GUARD_DE6D0AC9_F1A3_4A4E_90C8_FBAA690CD01A */
