#ifndef INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03
#define INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03

#include "typedef.h"

typedef struct {
  Set *symbols;
  Bool flag;
} Register;

void register_declaration(Set *, Sexp *);

#endif /* INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03 */
