#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "utility.h"

struct struct_Vector;
typedef struct struct_Vector Vector;

Vector *vector_new(Alignment);
void vector_free(Vector **);
Size vector_length(const Vector *);
boolean vector_empty(const Vector *);
void *vector_back(Vector *);
void *vector_at(Vector *, Index);
Vector *vector_clone(const Vector *);
void vector_append(Vector *, void *, Size);
void vector_clear(Vector *);
void vector_pop(Vector *);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
