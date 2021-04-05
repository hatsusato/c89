#ifndef INCLUDE_GUARD_693602CB_93F0_43D7_AEC7_D8B2330D470B
#define INCLUDE_GUARD_693602CB_93F0_43D7_AEC7_D8B2330D470B

#include "utility/types.h"

Sexp *ast_get_declaration_list(Sexp *);
Sexp *ast_get_statement_list(Sexp *);
Sexp *ast_get_function_type(Sexp *);
Sexp *ast_get_function_name(Sexp *);
Sexp *ast_get_function_body(Sexp *);
Sexp *ast_get_function_return_count(Sexp *);

#endif /* INCLUDE_GUARD_693602CB_93F0_43D7_AEC7_D8B2330D470B */
