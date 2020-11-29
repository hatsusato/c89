#ifndef INCLUDE_GUARD_CEF76A36_FC1B_4A04_BA5B_8E1A29C43165
#define INCLUDE_GUARD_CEF76A36_FC1B_4A04_BA5B_8E1A29C43165

#include "ir/register_type.h"

RegisterGenerator *register_generator_new(void);
void register_generator_delete(RegisterGenerator *);
void register_init(Register *);
void register_print(Register *);
void register_set(RegisterGenerator *, Register *);

#endif /* INCLUDE_GUARD_CEF76A36_FC1B_4A04_BA5B_8E1A29C43165 */
