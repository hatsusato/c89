#ifndef INCLUDE_GUARD_73005BDB_B13D_44DF_81E9_5D8719897410
#define INCLUDE_GUARD_73005BDB_B13D_44DF_81E9_5D8719897410

#include "typedef.h"

typedef struct {
  Set *symbols;
  Bool flag;
} Register;

void register_foreach(Register *, Sexp *, void (*)(Register *, Sexp *));
void register_is_typedef(Register *, Sexp *);

#endif /* INCLUDE_GUARD_73005BDB_B13D_44DF_81E9_5D8719897410 */
