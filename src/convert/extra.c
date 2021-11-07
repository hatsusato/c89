#include "extra.h"

#include "json/json.h"

void convert_extra_init(struct convert_extra *self, struct json *module) {
  self->module = module;
  self->function = json_new_obj();
}
