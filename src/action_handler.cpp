#include <log.h>
#include <action_handler.h>

pid_t __start_new_process(){
  return fork();
}

void __redirect_output(char* pk_out, char* pk_err){
  freopen(pk_out,"a+",stdout);
  freopen(pk_err,"a+",stderr);
}

void __pk_process(pk_proc *pkp_instance){
  pkp_instance->pid = getpid();
  LOG(L_MSG) << "proktor process started with pid:" << pkp_instance->pid;

  if(strlen(pkp_instance->file)){
    LOG(L_MSG) << "proktor process executing the binary with the file.";
    char *args[]= { pkp_instance->binary, pkp_instance->file, NULL};
    // execvp(pkp_instance->binary, args);
  }
  else{
    LOG(L_MSG) << "proktor process executing the binary.";
    char *args[] = { pkp_instance->binary, NULL};
    // execvp(pkp_instance->binary, args);
  }
}

void __monitor_process(pk_mon *pkm_instance, pk_proc *pkp_instance){
  __redirect_output(pkm_instance->log, pkm_instance->log);

  LOG(L_ERR) << "this should be in the new file.";

  pkm_instance->pid = pkp_instance->m_pid = getpid();
  LOG(L_MSG) << "monitor started with pid:" << pkp_instance->m_pid;

  pkp_instance->pid = __start_new_process();
  if(pkp_instance->pid == 0) __pk_process(pkp_instance);
}

bool validate_start_action_opts(pk_proc *pkp){
  // if(!strlen(pkp->name)) return false;
  // if(!strlen(pkp->file)) return false;
  if(!strlen(pkp->binary)) return false;

  return true;
}

int start_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;

  if(!validate_start_action_opts(pkp)){
    exit_process(0, VAL_START_AC_MSG);
  }

  pkm->pid = pkp->m_pid = __start_new_process();
  if(pkp->m_pid == 0) __monitor_process(pkm, pkp);
  FEND;
  return 0;
}

int stop_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}

int restart_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}

int status_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}
