#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "boolean.h"

struct struct_Vector;
typedef struct struct_Vector Vector;

Vector *vector_new(void);
Vector *vector_free(Vector *);
int vector_size(const Vector *);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
