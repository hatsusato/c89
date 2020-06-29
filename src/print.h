#ifndef INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0
#define INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0

#include "list.h"
#include "sexp.h"

void print_indent(int);
List *print_data(List *);
List *print_ast(List *, int);
List *print_consume(List *);
void print_sexp(Sexp *, int);

#endif /* INCLUDE_GUARD_D896553D_65DB_40A5_9407_DCA8043F53B0 */
