#ifndef INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0
#define INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0

#include <stdio.h>

#include "sexp.h"

void print_indent(FILE *, int);
void print_verbatim(FILE *, const char *, int);
void print_symbol(FILE *, Sexp *);
void print_sexp(Sexp *, int);

#endif /* INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0 */
