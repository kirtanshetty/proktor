#ifndef __PK_SRC_ACTION_HANDLER_H__
#define __PK_SRC_ACTION_HANDLER_H__

#include <proc.h>

#define VAL_HELP_MSG "Check option -h for help."
#define VAL_ERR_MSG(act, params) "Mandatory parameters for \'" act "\' action are: " params "\n" VAL_HELP_MSG
#define VAL_START_AC_MSG VAL_ERR_MSG("start", "-a -e")

int start_pk_proc(pk_proc* pkp);
int stop_pk_proc(pk_proc *pkp);
int restart_pk_proc(pk_proc *pkp);
int status_pk_proc(pk_proc *pkp);

typedef int (*action_handler)(pk_proc*);

struct __pk_proc_action_handlers {
  pk_proc_action_vals id;
  action_handler handler;
} pkpah_map[] = {
  [0].id = AC_START,
  [0].handler = start_pk_proc,

  [1].id = AC_STOP,
  [1].handler = stop_pk_proc,

  [2].id = AC_RESTART,
  [2].handler = restart_pk_proc,

  [3].id = AC_STATUS,
  [3].handler = status_pk_proc,
};

typedef struct __pk_proc_action_handlers pk_proc_action_handlers;

#endif
