#include <string.h>

#include <proc.h>
#include <action_handler.h>

pk_proc_h::pk_proc_h(pk_proc_options *ppo){
  printf("pk_proc_h::pk_proc_h\n");

  action = ppo->action;

  memset(&pkp, 0, sizeof(pkp));

  if(strlen(ppo->bin_path))
    strcpy(pkp.binary, ppo->bin_path);

  if(strlen(ppo->file_path))
    strcpy(pkp.file, ppo->file_path);

  if(strlen(ppo->pk_proc_name))
    strcpy(pkp.name, ppo->pk_proc_name);
}

void pk_proc_h::run(){
  pkpah_map[action].handler(&pkp);
}
