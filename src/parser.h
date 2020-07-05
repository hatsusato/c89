#ifndef INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD
#define INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD

#include "sexp.h"

#define PARSER_TAG(sym, ast) sexp_cons(sexp_symbol(#sym), ast)
#define PARSER_TOKEN(sym, scanner) \
  PARSER_TAG(sym, sexp_list1(scanner_token(scanner)))
#define PARSER_LIST_NIL(sym) PARSER_TAG(sym, sexp_nil())
#define PARSER_LIST_ATOM(sym, atom) PARSER_TAG(sym, sexp_list1(atom))
#define PARSER_LIST_PAIR(list, last) sexp_snoc(list, last)
#define PARSER_LIST0() sexp_nil()
#define PARSER_LIST1(ast0) sexp_cons(ast0, PARSER_LIST0())
#define PARSER_LIST2(ast0, ast1) sexp_cons(ast0, PARSER_LIST1(ast1))
#define PARSER_LIST3(ast0, ast1, ast2) sexp_cons(ast0, PARSER_LIST2(ast1, ast2))
#define PARSER_LIST4(ast0, ast1, ast2, ast3) \
  sexp_cons(ast0, PARSER_LIST3(ast1, ast2, ast3))
#define PARSER_LIST5(ast0, ast1, ast2, ast3, ast4) \
  sexp_cons(ast0, PARSER_LIST4(ast1, ast2, ast3, ast4))
#define PARSER_LIST6(ast0, ast1, ast2, ast3, ast4, ast5) \
  sexp_cons(ast0, PARSER_LIST5(ast1, ast2, ast3, ast4, ast5))
#define PARSER_LIST7(ast0, ast1, ast2, ast3, ast4, ast5, ast6) \
  sexp_cons(ast0, PARSER_LIST6(ast1, ast2, ast3, ast4, ast5, ast6))
#define PARSER_LIST8(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7) \
  sexp_cons(ast0, PARSER_LIST7(ast1, ast2, ast3, ast4, ast5, ast6, ast7))
#define PARSER_LIST9(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8) \
  sexp_cons(ast0, PARSER_LIST8(ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8))

#endif /* INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD */
