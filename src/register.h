#ifndef INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03
#define INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03

#include "typedef.h"

typedef struct {
  Set *symbols;
  Bool flag;
} Register;

Bool register_check_tag(Sexp *, const char *);
void register_is_typedef(Register *, Sexp *);
void register_identifier(Register *, Sexp *);
void register_foreach(Register *, Sexp *, void (*)(Register *, Sexp *));
void register_declaration(Set *, Sexp *);

#endif /* INCLUDE_GUARD_2F3411B7_BDBD_4EB1_815C_B08161816E03 */
