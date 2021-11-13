#ifndef INCLUDE_GUARD_95D65C5D_DF15_48DD_9B3A_3CC58AFF5BB2
#define INCLUDE_GUARD_95D65C5D_DF15_48DD_9B3A_3CC58AFF5BB2

#include "util/type.h"

struct json;

struct json *ir_instr_new(const char *);
void ir_instr_insert(struct json *, const char *, struct json *);
void ir_instr_icmp_cond(struct json *, struct json *);
bool_t ir_instr_check_kind(struct json *, const char *);
void ir_instr_set_numbering(struct json *, int);
bool_t ir_instr_has_numbering(struct json *);
int ir_instr_get_numbering(struct json *);

#endif /* INCLUDE_GUARD_95D65C5D_DF15_48DD_9B3A_3CC58AFF5BB2 */
