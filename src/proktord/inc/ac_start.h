#ifndef PK_INC_AC_START_H
#define PK_INC_AC_START_H

#include <proc.h>

int run_start_action(pk_mon *pkm_instance, pk_proc *pkp_instance);
bool validate_start_action_opts(pk_proc *pkp);

// pid_t __start_new_process();
// void __monitor_process(pk_mon *pkm_instance, pk_proc *pkp_instance);

#endif