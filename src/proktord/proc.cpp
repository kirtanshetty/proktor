#include <string.h>

#include <common.h>
#include <metadata.h>
#include <log.h>
#include <proc.h>
#include <action_handler.h>

pk_proc_h::pk_proc_h(pk_proc_options *ppo){
  FBEG;

  bool file_op = false;
  action = ppo->action;

  memset(&pkp, 0, sizeof(pkp));
  memset(&pkm, 0, sizeof(pkm));

  if(strlen(ppo->bin_path))
    strcpy(pkp.binary, ppo->bin_path);

  if(strlen(ppo->file_path)){
    file_op = true;
    strcpy(pkp.file, ppo->file_path);
  }

  if(strlen(ppo->pk_proc_name))
    strcpy(pkp.name, ppo->pk_proc_name);
  else{
    if(file_op)
      get_pk_proc_name_from_path(ppo->file_path, pkp.name, PK_PROC_NAME_TAG);
    else
      get_pk_proc_name_from_path(ppo->bin_path, pkp.name, PK_PROC_NAME_TAG);
  }

  get_pk_file(ppo->pk_log_path, pkm.log, PK_MON_LOG_FILE);
  get_pk_file(ppo->pk_log_path, pkm.pk_md, PK_METADATA_FILE);

  // get_pk_log_file(ppo->pk_proc_log_path, pkp.log, PK_MON_LOG_FILE);

  // LOG(L_DBG) << "pkp.name: " << pkp.name;
  // LOG(L_DBG) << "pkm.log: " << pkm.log;

  FEND;
}

void pk_proc_h::run(){
  pkpah_map[action].handler(&pkm, &pkp);
  // will execute for all child
}
