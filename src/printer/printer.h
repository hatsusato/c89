#ifndef INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3
#define INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3

#include "util/type.h"

struct printer;

struct printer *printer_new(void *);
struct printer *printer_new_stdout(void);
struct printer *printer_new_stderr(void);
void printer_delete(struct printer *);
void printer_print(struct printer *, const char *, ...);
void printer_newline(struct printer *);
void printer_indent(struct printer *, index_t);

#endif /* INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3 */
