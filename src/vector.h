#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "utility.h"

struct struct_Vector;
typedef struct struct_Vector Vector;

Size vector_alignment(void);
Vector *vector_new(void);
void vector_delete(Vector *);
Size vector_length(const Vector *);
void *vector_back(Vector *);
void vector_push(Vector *, const void *);
void *vector_begin(Vector *);
void *vector_end(Vector *);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
