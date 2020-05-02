#include <log.h>
#include <action_handler.h>

pid_t __start_new_process(){
  return fork();
}

void __pk_process(pk_proc *pkp_instance){
  pkp_instance->pid = getpid();
  LOG(L_MSG) << "proktor process started with pid:" << pkp_instance->pid;

  if(!strlen(pkp_instance->file)){
    LOG(L_MSG) << "proktor process executing the binary.";
    // execvp(pkp_instance->binary, NULL);
  }
}

void __monitor_process(pk_proc *pkp_instance){
  pkp_instance->m_pid = getpid();
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

int start_pk_proc(pk_proc *pkp){
  FBEG;

  if(!validate_start_action_opts(pkp)){
    exit_process(0, VAL_START_AC_MSG);
  }

  pkp->m_pid = __start_new_process();
  if(pkp->m_pid == 0) __monitor_process(pkp);
  FEND;
  return 0;
}

int stop_pk_proc(pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}

int restart_pk_proc(pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}

int status_pk_proc(pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}
