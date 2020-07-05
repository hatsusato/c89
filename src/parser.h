#ifndef INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD
#define INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD

#include "sexp.h"

#define PARSER_TAG(sym, ast) sexp_cons(sexp_symbol(#sym), ast)
#define PARSER_TOKEN(sym, scanner) \
  PARSER_TAG(sym, sexp_list1(scanner_token(scanner)))
#define PARSER_LIST_NIL(sym) PARSER_TAG(sym, sexp_nil())
#define PARSER_LIST_ATOM(sym, atom) PARSER_TAG(sym, sexp_list1(atom))
#define PARSER_LIST_PAIR(list, last) sexp_snoc(list, last)

#endif /* INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD */
