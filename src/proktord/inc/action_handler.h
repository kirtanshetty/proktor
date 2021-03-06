#ifndef __PK_SRC_ACTION_HANDLER_H__
#define __PK_SRC_ACTION_HANDLER_H__

#include <common.h>
#include <proc.h>

#define VAL_HELP_MSG "Check option -h for help."
#define VAL_ERR_MSG(act, params) "Mandatory parameters for \'" act "\' action are: " params "\n" VAL_HELP_MSG
#define VAL_START_AC_MSG VAL_ERR_MSG("start", "-a -e")

int start_pk_proc(pk_mon *pkm, pk_proc *pkp);
int stop_pk_proc(pk_mon *pkm, pk_proc *pkp);
int restart_pk_proc(pk_mon *pkm, pk_proc *pkp);
int status_pk_proc(pk_mon *pkm, pk_proc *pkp);
int none_pk_proc(pk_mon *pkm, pk_proc *pkp);

typedef int (*action_handler)(pk_mon*, pk_proc*);

struct __pk_proc_action_handlers {
  pk_proc_action_vals id;
  action_handler handler;
} pkpah_map[] = {
  [0].id = AC_NONE,
  [0].handler = none_pk_proc,

  [1].id = AC_START,
  [1].handler = start_pk_proc,

  [2].id = AC_STOP,
  [2].handler = stop_pk_proc,

  [3].id = AC_RESTART,
  [3].handler = restart_pk_proc,

  [4].id = AC_STATUS,
  [4].handler = status_pk_proc,
};

typedef struct __pk_proc_action_handlers pk_proc_action_handlers;

#endif
