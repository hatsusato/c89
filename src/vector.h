#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "utility.h"

struct struct_Vector;
typedef struct struct_Vector Vector;
typedef void (*VectorDestructor)(const void *);

Size vector_alignment(void);
Vector *vector_new(void);
void vector_delete(Vector *);
Size vector_length(const Vector *);
const void **vector_begin(const Vector *);
const void **vector_end(const Vector *);
void vector_push(Vector *, const void *);
void vector_pop(Vector *, VectorDestructor);
void vector_clean(Vector *, VectorDestructor);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
