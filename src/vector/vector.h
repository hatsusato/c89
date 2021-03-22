#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "utility/types.h"
#include "vector/typedef.h"

Vector *vector_new(VectorDestructor);
void vector_delete(Vector *);
void vector_destruct(const Vector *, VectorElem);
Bool vector_empty(const Vector *);
Size vector_length(const Vector *);
Size vector_capacity(const Vector *);
VectorElem *vector_begin(const Vector *);
VectorElem *vector_end(const Vector *);
VectorElem vector_front(const Vector *);
VectorElem vector_back(const Vector *);
VectorElem vector_at(const Vector *, Index);
void vector_push(Vector *, VectorElem);
void vector_pop(Vector *);
void vector_clear(Vector *);
void vector_sort(Vector *, VectorCmp);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
