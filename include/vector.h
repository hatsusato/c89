#ifndef INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E
#define INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E

#include "types.h"

struct struct_Vector;
typedef struct struct_Vector Vector;

Vector *vector_new(Destructor);
void vector_delete(Vector *);
void vector_destruct(Vector *, ElemType);
Size vector_length(const Vector *);
ElemType *vector_begin(const Vector *);
ElemType *vector_end(const Vector *);
ElemType vector_front(const Vector *);
ElemType vector_back(const Vector *);
void vector_push(Vector *, ElemType);
void vector_pop(Vector *);
void vector_clear(Vector *);

#endif /* INCLUDE_GUARD_228B134A_0631_479A_9421_9C226E168C9E */
