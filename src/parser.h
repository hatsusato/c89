#ifndef INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD
#define INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD

#include "struct.h"

#define PARSER_SYMBOL(sym) parser_symbol(#sym)
#define PARSER_TAG(sym, ast) parser_tag(#sym, ast)
#define PARSER_TOKEN(sym, scanner) parser_token(#sym, scanner)
#define PARSER_NIL(sym) PARSER_LIST1(PARSER_SYMBOL(sym))
#define PARSER_ATOM(sym, atom) PARSER_LIST2(PARSER_SYMBOL(sym), atom)
#define PARSER_SNOC(list, last) parser_snoc(list, last)
#define PARSER_CONS(car, cdr) parser_cons(car, cdr);
#define PARSER_LIST0() parser_nil()
#define PARSER_LIST1(ast0) parser_cons(ast0, PARSER_LIST0())
#define PARSER_LIST2(ast0, ast1) parser_cons(ast0, PARSER_LIST1(ast1))
#define PARSER_LIST3(ast0, ast1, ast2) \
  parser_cons(ast0, PARSER_LIST2(ast1, ast2))
#define PARSER_LIST4(ast0, ast1, ast2, ast3) \
  parser_cons(ast0, PARSER_LIST3(ast1, ast2, ast3))
#define PARSER_LIST5(ast0, ast1, ast2, ast3, ast4) \
  parser_cons(ast0, PARSER_LIST4(ast1, ast2, ast3, ast4))
#define PARSER_LIST6(ast0, ast1, ast2, ast3, ast4, ast5) \
  parser_cons(ast0, PARSER_LIST5(ast1, ast2, ast3, ast4, ast5))
#define PARSER_LIST7(ast0, ast1, ast2, ast3, ast4, ast5, ast6) \
  parser_cons(ast0, PARSER_LIST6(ast1, ast2, ast3, ast4, ast5, ast6))
#define PARSER_LIST8(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7) \
  parser_cons(ast0, PARSER_LIST7(ast1, ast2, ast3, ast4, ast5, ast6, ast7))
#define PARSER_LIST9(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8) \
  parser_cons(ast0,                                                        \
              PARSER_LIST8(ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8))

Sexp *parser_symbol(const char *);
Sexp *parser_tag(const char *, Sexp *);
Sexp *parser_token(const char *, yyscan_t);
Sexp *parser_nil(void);
Sexp *parser_cons(Sexp *, Sexp *);
Sexp *parser_snoc(Sexp *, Sexp *);

#endif /* INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD */
