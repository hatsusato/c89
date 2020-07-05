#include "print.h"

#include <ctype.h>

static void print_sexp_list(FILE *fp, Sexp *sexp, int indent) {
  assert(sexp_is_pair(sexp));
  print_sexp(fp, sexp_car(sexp), indent);
  for (sexp = sexp_cdr(sexp); sexp_is_pair(sexp); sexp = sexp_cdr(sexp)) {
    fprintf(fp, "\n");
    print_indent(fp, indent);
    print_sexp(fp, sexp_car(sexp), indent);
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
    fprintf(fp, "%s", sexp_get(sexp));
  }
}
void print_sexp(FILE *fp, Sexp *sexp, int indent) {
  const char *prefix = "(", *suffix = ")";
  if (sexp_is_pair(sexp)) {
    fprintf(fp, "%s", prefix);
    print_sexp_list(fp, sexp, indent + 1);
    fprintf(fp, "%s", suffix);
  } else {
    if (sexp_is_symbol(sexp)) {
      const char *sym = sexp_get(sexp);
      assert(sym);
      prefix = suffix = (isalpha(*sym) ? "" : "#");
    } else if (sexp_is_string(sexp)) {
      prefix = suffix = "\"";
    }
    fprintf(fp, "%s", prefix);
    print_symbol(fp, sexp);
    fprintf(fp, "%s", suffix);
  }
}
