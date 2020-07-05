#include "print.h"

#include <ctype.h>

void print_indent(FILE *fp, int indent) {
  for (; 0 < indent; --indent) {
    fprintf(fp, " ");
  }
}
void print_verbatim(FILE *fp, const char *text, int leng) {
  int i = 0;
  for (i = 0; i < leng; ++i) {
    char c = text[i];
    if (isprint(c)) {
      fprintf(fp, "%c", c);
    } else {
      fprintf(fp, "\\x%02x", (unsigned char)c);
    }
  }
}
void print_symbol(Sexp *sexp) {
  if (sexp_is_symbol(sexp) || sexp_is_string(sexp)) {
    printf("%s", sexp_get_string(sexp));
  }
}
static void print_sexp_list(Sexp *sexp, int indent) {
  if (sexp_is_pair(sexp)) {
    printf("\n");
    print_indent(stdout, indent);
    print_sexp(sexp_car(sexp), indent);
    print_sexp_list(sexp_cdr(sexp), indent);
  } else {
    assert(sexp_is_nil(sexp));
  }
}
void print_sexp(Sexp *sexp, int indent) {
  if (sexp_is_pair(sexp)) {
    printf("(");
    print_sexp(sexp_car(sexp), indent + 1);
    print_sexp_list(sexp_cdr(sexp), indent + 1);
    printf(")");
  } else if (sexp_is_symbol(sexp)) {
    assert(sexp_get_string(sexp));
    if (!isalpha(*sexp_get_string(sexp))) {
      printf("#");
    }
    print_symbol(sexp);
  } else if (sexp_is_string(sexp)) {
    printf("%c", '"');
    print_symbol(sexp);
    printf("%c", '"');
  } else {
    printf("()");
  }
}
