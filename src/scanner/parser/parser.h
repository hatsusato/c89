#ifndef INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD
#define INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD

#define PARSER_SYMBOL(tag) sexp_number(tag)
#define PARSER_TAG(tag, list) sexp_pair(sexp_number(tag), list)
#define PARSER_CONS(car, cdr) sexp_pair(car, cdr)
#define PARSER_LIST0() sexp_nil()
#define PARSER_LIST1(ast0) PARSER_CONS(ast0, PARSER_LIST0())
#define PARSER_LIST2(ast0, ast1) PARSER_CONS(ast0, PARSER_LIST1(ast1))
#define PARSER_LIST3(ast0, ast1, ast2) \
  PARSER_CONS(ast0, PARSER_LIST2(ast1, ast2))
#define PARSER_LIST4(ast0, ast1, ast2, ast3) \
  PARSER_CONS(ast0, PARSER_LIST3(ast1, ast2, ast3))
#define PARSER_LIST5(ast0, ast1, ast2, ast3, ast4) \
  PARSER_CONS(ast0, PARSER_LIST4(ast1, ast2, ast3, ast4))
#define PARSER_LIST6(ast0, ast1, ast2, ast3, ast4, ast5) \
  PARSER_CONS(ast0, PARSER_LIST5(ast1, ast2, ast3, ast4, ast5))
#define PARSER_LIST7(ast0, ast1, ast2, ast3, ast4, ast5, ast6) \
  PARSER_CONS(ast0, PARSER_LIST6(ast1, ast2, ast3, ast4, ast5, ast6))
#define PARSER_LIST8(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7) \
  PARSER_CONS(ast0, PARSER_LIST7(ast1, ast2, ast3, ast4, ast5, ast6, ast7))
#define PARSER_LIST9(ast0, ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8) \
  PARSER_CONS(ast0,                                                        \
              PARSER_LIST8(ast1, ast2, ast3, ast4, ast5, ast6, ast7, ast8))
#define PARSER_LIST_NIL(tag) PARSER_LIST1(sexp_number(tag))
#define PARSER_LIST_ATOM(tag, ast) PARSER_LIST2(sexp_number(tag), ast)
#define PARSER_LIST_SNOC(list, ast) sexp_snoc(list, ast)

#endif /* INCLUDE_GUARD_084F183E_587F_408F_9792_59D56118F8FD */
