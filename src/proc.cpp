#include <string.h>

#include "inc/proc.h"
#include "inc/action_handler.h"

pk_proc_h::pk_proc_h(pk_proc_options *ppo){
  printf("pk_proc_h::pk_proc_h\n");
  pk_proc _pkp;
  strcpy(_pkp.file, ppo->bin_path);
  strcpy(_pkp.name, ppo->pk_proc_name);

  switch(ppo->action){
    case AC_START:
      start_pk_proc(&_pkp);
      break;
    case AC_STOP:
      stop_pk_proc();
      break;
    case AC_RESTART:
      restart_pk_proc();
      break;
    case AC_STATUS:
      status_pk_proc();
      break;
    default:{

    }
  }
}
