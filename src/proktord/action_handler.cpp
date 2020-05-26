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
  LOG(L_MSG) << "proktor process executing the binary: " << pkp_instance->binary;
  char *argx[]= { pkp_instance->binary, strlen(pkp_instance->file) ? pkp_instance->file : NULL , NULL};
  // EXECTION_CMD(pkp_instance->binary, argx);
}

void __monitor_process(pk_mon *pkm_instance, pk_proc *pkp_instance){
  __redirect_output(pkm_instance->log, pkm_instance->log);

  bool is_new_proc = true;
  pkm_instance->pid = getpid();
  pkp_instance->m_pid = getpid();
  LOG(L_MSG) << "monitor started with pid:" << pkp_instance->m_pid << ", iid:" << pkp_instance->iid;

  while(true){
    // Decide instance iid
    proc_list_buf plb;
    memset(&plb, 0, sizeof(proc_list_buf));
    init_proc_list(pkm_instance->pk_md, &plb);

    if(plb.map){
      printf("length %u\n", plb.map->len);
    }

    if(is_new_proc){
      if(!pkp_instance->uuid){
        get_uuid_for_proc(pkp_instance, plb.map);
        if(!pkp_instance->uuid)
          exit_process(0, "number of uuid's exhausted");

        LOG(L_DBG) << "new uuid : " << pkp_instance->uuid;
      }

      if(!pkp_instance->iid){
        get_iid_for_proc(pkp_instance, plb.map);
        LOG(L_DBG) << "new iid : " << pkp_instance->iid;
      }

      if(is_used_instance_id(pkp_instance, plb.map)){
        LOG(L_FAT) << "instance id taken already : " << pkp_instance->iid;
        exit_process(0, "please provide a unique instance id.");
      }

      add_proc_to_list(pkp_instance, &plb);
      print_proc_list(plb.map);
    }
    else if(pkp_instance->st == ST_STOPPED){
    // else {
      LOG(L_MSG) << "Updating the proktor list before stopping";
      pkp_instance->pid = 0;
      pkp_instance->m_pid = 0;
      update_proc_obj(pkp_instance, plb.map);
      print_proc_list(plb.map);
      commit_proc_list(pkm_instance->pk_md, &plb);
      deinit_proc_list(&plb);
      LOG(L_MSG) << "proktor monitor exitting";
      break;
    }

    // print_proc_list(plb.map);

    is_new_proc = false;
    pkp_instance->pid = __start_new_process();

    if(pkp_instance->pid == 0){
      __pk_process(pkp_instance);
      return;
    }
    else{
      pkp_instance->st = ST_RUNNING;
      commit_proc_list(pkm_instance->pk_md, &plb);
      deinit_proc_list(&plb);

      LOG(L_MSG) << "waiting for the child process " << pkp_instance->name << "(" << pkp_instance->pid << ")";
      int wait_stat;
      wait(&wait_stat);
      LOG(L_MSG) << "child process " << pkp_instance->name << "(" << pkp_instance->pid << ")" << " terminated with rc " << wait_stat;

      pk_proc_valid_signal(wait_stat) ? pkp_instance->st = ST_STOPPED : pkp_instance->st = ST_KILLED;

      // proc_list_buf plb;
      // memset(&plb, 0, sizeof(proc_list_buf));
      // init_proc_list(pkm_instance->pk_md, &plb);
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

int none_pk_proc(pk_mon *pkm, pk_proc *pkp){
  FBEG;
  FEND;
  return 0;
}