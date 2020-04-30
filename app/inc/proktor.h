#ifndef __PK_APP_PROKTOR_H__
#define __PK_APP_PROKTOR_H__

#include "../../src/inc/proc.h"

typedef int (*action_handler)(pk_proc*);

struct __pk_proc_action {
  const char* action;
  pk_proc_action_vals id;
} pkpa_map[] = {
  [0].action = "start",
  [0].id = AC_START,

  [1].action = "stop",
  [1].id = AC_STOP,

  [2].action = "restart",
  [2].id = AC_RESTART,

  [3].action = "status",
  [3].id = AC_STATUS,
};

typedef struct __pk_proc_action pk_proc_action;

uint8_t pkpa_map_length = sizeof(pkpa_map)/sizeof(pk_proc_action);

#endif
