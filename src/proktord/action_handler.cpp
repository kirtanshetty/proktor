#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <log.h>
#include <proc.h>
#include <action_handler.h>
#include <common.h>
#include <utils.h>
#include <metadata.h>


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

  if(fd_out < 0){
    LOG(L_FAT) << "Couldn't create output log file for monitor process at " << pk_out << " , rc " << fd_out;
    exit_process(1, "Unable to create log file");
  }

  if(fd_err < 0){
    LOG(L_FAT) << "Couldn't create error log file for monitor process at " << pk_err << " , rc " << fd_err;
    exit_process(1, "Unable to create log file");
  }

  LOG(L_DBG) << "__redirect_output:pk_out:" << pk_out << ":" << fd_out;
  LOG(L_DBG) << "__redirect_output:pk_err:" << pk_err << ":" << fd_err;

  dup2(fd_out, STDOUT_FD);
  dup2(fd_err, STDERR_FD);

  // close(STDOUT_FD);
  // close(STDERR_FD);
}

void __pk_process(pk_proc *pkp_instance){
  pkp_instance->pid = getpid();
  LOG(L_MSG) << "proktor process started with pid:" << pkp_instance->pid;
  printf("-----------------\n");
  LOG(L_MSG) << "proktor process executing the binary: " << pkp_instance->binary;
  char *argx[]= { pkp_instance->binary, strlen(pkp_instance->file) ? pkp_instance->file : NULL , NULL};
  // EXECTION_CMD(pkp_instance->binary, argx);
}

void __monitor_process(pk_mon *pkm_instance, pk_proc *pkp_instance){
  __redirect_output(pkm_instance->log, pkm_instance->log);

  pkm_instance->pid = pkp_instance->m_pid = getpid();
  LOG(L_MSG) << "monitor started with pid:" << pkp_instance->m_pid << ", iid:" << pkp_instance->iid;

  while(true){
    // Decide instance iid
    LOG(L_MSG) << "outside iid:" << pkp_instance->iid;
    if(!pkp_instance->iid){
      pkp_instance->iid = 1;
      LOG(L_MSG) << "inside iid:" << pkp_instance->iid;
      proc_list_buf plb;
      printf("before: plb %d\n", plb);
      printf("before: plb %p\n", &plb);
      printf("before: plb.list %p\n", &plb.list);
      memset(&plb, 0, sizeof(proc_list_buf));
      printf("before: plb %d\n", plb);

      // sleep(5);

      get_proc_list(pkm_instance->pk_md, &plb);
      add_proc_to_list(pkp_instance, &plb);
      // dump_proc_list(pkm_instance->pk_md, &plb);

      printf("after pkp_instance->pid %d\n", pkp_instance->pid);
      printf("after pkp_instance->m_pid %d\n", pkp_instance->m_pid);
      printf("after pkp_instance->name %s\n", pkp_instance->name);

      printf("after get_proc_list: plb %p\n", plb);
      printf("after get_proc_list: &plb.list %p\n", &plb.list);
      printf("after get_proc_list: plb.list->length %d\n", plb.list->length);
      printf("after get_proc_list: plb.list[0].name %s\n", plb.list->entries[0].name);

      LOG(L_DBG) << "plb.list->entries[0].pid : " << plb.list->entries[0].pid;
      LOG(L_DBG) << "plb.list->entries[0].m_pid : " << plb.list->entries[0].m_pid;
      LOG(L_DBG) << "plb.list->entries[0].name : " << plb.list->entries[0].name;
      LOG(L_DBG) << "plb.list->entries[0].binary : " << plb.list->entries[0].binary;
      LOG(L_DBG) << "plb.list->entries[0].log : " << plb.list->entries[0].log;

      LOG(L_DBG) << "plb.list->entries[1].pid : " << plb.list->entries[1].pid;
      LOG(L_DBG) << "plb.list->entries[1].m_pid : " << plb.list->entries[1].m_pid;
      LOG(L_DBG) << "plb.list->entries[1].name : " << plb.list->entries[1].name;
      LOG(L_DBG) << "plb.list->entries[1].binary : " << plb.list->entries[1].binary;
      LOG(L_DBG) << "plb.list->entries[1].log : " << plb.list->entries[1].log;

      // printf("after get_proc_list: plb.list addr %d\n", ((uint16_t*)(&plb.list))[0]);
      // LOG(L_DBG) << "plb.list->length" << plb.list->length;
      // printf("after get_proc_list: plb length %d\n", plb.list->length);
      // add_proc_to_list(pkp_instance, &plb);
      // dump_proc_list(pkm_instance->pk_md, &plb);

      printf("after: plb %p\n", &plb);
      printf("after: plb.list %p\n", &plb.list);
      // LOG(L_MSG) << "plb.list.length:" << plb.list->length;
    }

    pkp_instance->pid = __start_new_process();
    if(pkp_instance->pid == 0){
      __pk_process(pkp_instance);
      return;
    }
    else{
      // update metadata.
      LOG(L_MSG) << "waiting for the child process " << pkp_instance->name << "(" << pkp_instance->pid << ")";
      int wait_stat;
      wait(&wait_stat);
      LOG(L_MSG) << "child process " << pkp_instance->name << "(" << pkp_instance->pid << ")" << " terminated with rc " << wait_stat;
      if(!pk_proc_valid_exit(wait_stat)){
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
