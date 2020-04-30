#include <string.h>

#include "inc/proc.h"
#include "inc/action_handler.h"

pk_proc_h::pk_proc_h(pk_proc_options *ppo){
  printf("pk_proc_h::pk_proc_h\n");
  pk_proc _pkp;
  strcpy(_pkp.file, ppo->bin_path);
  strcpy(_pkp.name, ppo->pk_proc_name);

  pkpah_map[ppo->action].handler(&_pkp);
}
