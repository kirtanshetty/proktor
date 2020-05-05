#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <log.h>
#include <action_handler.h>
#include <common.h>


#define OPEN_LOG(file) open(file, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR)
#define EXECTION_CMD execvp

#define STDOUT_FD 1
#define STDERR_FD 2

pid_t __start_new_process(){
  return fork();
}

void __redirect_output(char* pk_out, char* pk_err){
  int fd_out = OPEN_LOG(pk_out);
  int fd_err = OPEN_LOG(pk_err);

  printf("__redirect_output:fd_out %d\n", fd_out);
  printf("__redirect_output:fd_err %d\n", fd_err);

  if(fd_out < 0){
    LOG(L_FAT) << "Couldn't create output log file for monitor process at " << pk_out << " , rc " << fd_out;
    exit_process(1, "Unable to create log file");
  }

  if(fd_err < 0){
    LOG(L_FAT) << "Couldn't create error log file for monitor process at " << pk_err << " , rc " << fd_err;
    exit_process(1, "Unable to create log file");
  }

  dup2(fd_out, STDOUT_FD);
  dup2(fd_err, STDERR_FD);
}

void __pk_process(pk_proc *pkp_instance){
  __redirect_output("/Users/kirtan/personal/proktor/proktor.out", "/Users/kirtan/personal/proktor/proktor.out");
  pkp_instance->pid = getpid();
  LOG(L_MSG) << "proktor process started with pid:" << pkp_instance->pid;

  if(strlen(pkp_instance->file)){
    LOG(L_MSG) << "proktor process executing the binary with the file.";
    char *args[]= { pkp_instance->binary, pkp_instance->file, NULL};
    EXECTION_CMD(pkp_instance->binary, args);
  }
  else{
    LOG(L_MSG) << "proktor process executing the binary.";
    char *args[] = { pkp_instance->binary, NULL};
    EXECTION_CMD(pkp_instance->binary, args);
  }
}

void __monitor_process(pk_mon *pkm_instance, pk_proc *pkp_instance){
  __redirect_output(pkm_instance->log, pkm_instance->log);

  pkm_instance->pid = pkp_instance->m_pid = getpid();
  LOG(L_MSG) << "monitor started with pid:" << pkp_instance->m_pid;

  while(true){
    // Decide instance iid
    if(!pkp_instance->iid) pkp_instance->iid = 1;

    pkp_instance->pid = __start_new_process();
    if(pkp_instance->pid == 0){
      __pk_process(pkp_instance);
      return;
    }
    else{
      LOG(L_MSG) << "waiting for the child process " << pkp_instance->name << "(" << pkp_instance->pid << ")";
      int wait_stat;
      wait(&wait_stat);
      LOG(L_MSG) << "child process " << pkp_instance->name << "(" << pkp_instance->pid << ")" << " terminated with rc " << wait_stat;
      if(!pk_proc_restart(wait_stat)){
        LOG(L_MSG) << "exiting monitor for " << pkp_instance->name;
        break;
      }
    }
  }
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
