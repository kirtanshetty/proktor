#ifndef __PK_APP_COMMON_H__
#define __PK_APP_COMMON_H__

#include <unistd.h>

#include "proktor.h"

#define LINE_DIVISION "-----------------------------------------------\n"
#define TAB_SPACE "  "

pk_proc_action pkpa_map[] = {
  [0].action = "start",
  [0].id = AC_START,

  [1].action = "stop",
  [1].id = AC_STOP,

  [2].action = "restart",
  [2].id = AC_RESTART,

  [3].action = "status",
  [3].id = AC_STATUS,
};

uint8_t pkpa_map_length = sizeof(pkpa_map)/sizeof(pk_proc_action);

#endif
