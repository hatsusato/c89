#include "print.h"

#include <ctype.h>

static void print_sexp_list(FILE *fp, Sexp *sexp, int indent) {
  if (sexp_is_pair(sexp)) {
    fprintf(fp, "\n");
    print_indent(fp, indent);
    print_sexp(fp, sexp_car(sexp), indent);
    print_sexp_list(fp, sexp_cdr(sexp), indent);
  } else {
    assert(sexp_is_nil(sexp));
  }
}

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
void print_symbol(FILE *fp, Sexp *sexp) {
  if (sexp_is_symbol(sexp) || sexp_is_string(sexp)) {
    fprintf(fp, "%s", sexp_get_string(sexp));
  }
}
void print_sexp(FILE *fp, Sexp *sexp, int indent) {
  if (sexp_is_pair(sexp)) {
    fprintf(fp, "(");
    print_sexp(fp, sexp_car(sexp), indent + 1);
    print_sexp_list(fp, sexp_cdr(sexp), indent + 1);
    fprintf(fp, ")");
  } else if (sexp_is_symbol(sexp)) {
    assert(sexp_get_string(sexp));
    if (!isalpha(*sexp_get_string(sexp))) {
      fprintf(fp, "#");
    }
    print_symbol(fp, sexp);
  } else if (sexp_is_string(sexp)) {
    fprintf(fp, "%c", '"');
    print_symbol(fp, sexp);
    fprintf(fp, "%c", '"');
  } else {
    fprintf(fp, "()");
  }
}
