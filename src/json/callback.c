#include "callback.h"

struct json_callback {
  json_callback_t callback;
  struct json_obj *args;
};
