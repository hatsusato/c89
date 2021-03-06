#ifndef INCLUDE_GUARD_E88AF2CB_9E19_4C46_83B0_440BEC63AA1B
#define INCLUDE_GUARD_E88AF2CB_9E19_4C46_83B0_440BEC63AA1B

#include "utility/types.h"

struct struct_TypeSpec;
typedef struct struct_TypeSpec TypeSpec;

typedef enum {
  TYPE_SPEC_VOID,
  TYPE_SPEC_CHAR,
  TYPE_SPEC_SHORT,
  TYPE_SPEC_INT,
  TYPE_SPEC_LONG,
  TYPE_SPEC_FLOAT,
  TYPE_SPEC_DOUBLE,
  TYPE_SPEC_SIGNED,
  TYPE_SPEC_UNSIGNED,
  TYPE_SPEC_COUNT
} TypeSpecIndex;

TypeSpec *type_spec_new(void);
void type_spec_delete(TypeSpec *);
void type_spec_set(TypeSpec *, TypeSpecIndex);
void type_spec_reset(TypeSpec *);
void type_init_spec(Type *, TypeSpec *);
Type *type_new_from_spec(Module *, TypeSpec *);

#endif /* INCLUDE_GUARD_E88AF2CB_9E19_4C46_83B0_440BEC63AA1B */
