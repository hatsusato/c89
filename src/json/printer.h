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
  void *extra;
};

void json_printer_print(struct json_printer *, struct json *);

#endif /* INCLUDE_GUARD_D0DB261A_1139_4CC7_A9C5_00F0E9573E21 */
