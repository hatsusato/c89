#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "utility/types.h"
#include "vector/types.h"

Vector *vector_new(Destructor);
void vector_delete(Vector *);
void vector_destruct(const Vector *, ElemType);
Bool vector_empty(const Vector *);
Size vector_length(const Vector *);
Size vector_capacity(const Vector *);
ElemType *vector_begin(const Vector *);
ElemType *vector_end(const Vector *);
ElemType vector_front(const Vector *);
ElemType vector_back(const Vector *);
ElemType vector_at(const Vector *, Index);
void vector_push(Vector *, ElemType);
void vector_pop(Vector *);
void vector_clear(Vector *);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
