#ifndef INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691
#define INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691

struct json;

void convert_alloc_init(struct json *);
struct json *convert_alloc_finish(struct json *);
struct json *convert_alloc_push(struct json *);

#endif /* INCLUDE_GUARD_32CB7D30_59B7_4E51_B3E4_18C6F8B85691 */
