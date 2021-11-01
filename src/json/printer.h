#ifndef INCLUDE_GUARD_D0DB261A_1139_4CC7_A9C5_00F0E9573E21
#define INCLUDE_GUARD_D0DB261A_1139_4CC7_A9C5_00F0E9573E21

#include "util/type.h"

struct json;
struct printer;

struct json_printer_extra {
  struct printer *printer;
  bool_t first;
};
struct json_printer {
  struct printer *printer;
  bool_t first;
};

void json_printer_recurse(struct json_printer *, struct json *);
void json_printer_newline(struct json_printer *);
void json_printer_open(struct json_printer *, const char *);
void json_printer_close(struct json_printer *, const char *);
void json_printer_comma(struct json_printer *);
void json_printer_symbol(struct json_printer *, const char *);
void json_printer_str(struct json_printer *, const char *);

#endif /* INCLUDE_GUARD_D0DB261A_1139_4CC7_A9C5_00F0E9573E21 */
