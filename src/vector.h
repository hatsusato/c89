#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "typedef.h"

Size vector_alignment(void);
Vector *vector_new(void);
void vector_delete(Vector *);
Size vector_length(const Vector *);
VectorElem *vector_begin(const Vector *);
VectorElem *vector_end(const Vector *);
VectorElem vector_front(const Vector *);
VectorElem vector_back(const Vector *);
void vector_push(Vector *, VectorElem);
void vector_pop(Vector *, VectorDestructor);
void vector_clear(Vector *, VectorDestructor);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
