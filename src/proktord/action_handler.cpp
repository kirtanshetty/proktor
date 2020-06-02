#include <log.h>
#include <action_handler.h>
#include <ac_start.h>
#include <common.h>

int start_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;

  init_proc_obj(pkp, pkm->pk_md);

  if(!validate_start_action_opts(pkp)){
    exit_process(0, VAL_START_AC_MSG);
  }

  int rc = run_start_action(pkm, pkp);

  // will execute for all child
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

int none_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}