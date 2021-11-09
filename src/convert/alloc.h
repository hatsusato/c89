#ifndef INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691
#define INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691

struct convert;
struct json;

void convert_alloc_init(struct convert *);
struct json *convert_alloc_finish(struct convert *);

#endif /* INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691 */
