#ifndef INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3
#define INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3

#include "util/type.h"

struct printer;

struct printer *printer_new(void *);
struct printer *printer_new_stdout(void);
struct printer *printer_new_stderr(void);
void printer_del(struct printer *);
void printer_print(struct printer *, const char *, ...);
void printer_quote(struct printer *, const char *);
void printer_newline(struct printer *);
void printer_open(struct printer *, const char *);
void printer_close(struct printer *, const char *);

#endif /* INCLUDE_GUARD_BF8EE8FD_9DC0_4D83_BCEE_4E488C1C49F3 */
