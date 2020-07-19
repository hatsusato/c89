#ifndef INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD
#define INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD

#include "ast.h"
#include "typedef.h"

#define PARSER_SYMBOL(tag) parser_symbol(AST_##tag)
#define PARSER_TAG(tag, ast) parser_tag(AST_##tag, ast)
#define PARSER_TOKEN(scanner) parser_token(scanner)
#define PARSER_NIL(tag) PARSER_TAG(tag, PARSER_LIST0())
#define PARSER_ATOM(sym, atom) PARSER_TAG(sym, PARSER_LIST1(atom))
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

Sexp *parser_symbol(AstTag);
Sexp *parser_tag(AstTag, Sexp *);
Sexp *parser_token(yyscan_t);
Sexp *parser_nil(void);
Sexp *parser_cons(Sexp *, Sexp *);
Sexp *parser_snoc(Sexp *, Sexp *);

#endif /* INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD */
