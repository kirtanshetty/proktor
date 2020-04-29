#ifndef __PK_SRC_ACTION_HANDLER_H__
#define __PK_SRC_ACTION_HANDLER_H__

#include "proc.h"

int start_pk_proc(pk_proc* pkp);
int stop_pk_proc();
int restart_pk_proc();
int status_pk_proc();

#endif
