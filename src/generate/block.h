#ifndef INCLUDE_GUARD_10F6B4A1_4FBA_40B7_B025_2E9477281B14
#define INCLUDE_GUARD_10F6B4A1_4FBA_40B7_B025_2E9477281B14

struct json;
struct printer;

void generate_block(struct printer *, struct json *);
void generate_block_label(struct printer *, struct json *);

#endif /* INCLUDE_GUARD_10F6B4A1_4FBA_40B7_B025_2E9477281B14 */
