#ifndef __PK_SRC_PROC_H__
#define __PK_SRC_PROC_H__

#include "common.h"

typedef uint8_t pk_inst_t;
typedef char pk_name_t;

typedef enum {
  ST_UNAVAILABLE,
  ST_RUNNING,
  ST_STOPPED
} pk_proc_status;

typedef enum {
  AC_START,
  AC_STOP,
  AC_RESTART,
  AC_STATUS
} pk_proc_action_vals;

// options accepted by the process handler
typedef struct __pk_proc_options{
  pk_proc_action_vals action;
  pk_name_t pk_proc_name[PK_PROC_NAME_LENGTH];
  pk_name_t bin_path[FILE_PATH_LENGTH];
} pk_proc_options;

// definition of a process
typedef struct __pk_proc {
  pid_t pid;
  pk_inst_t iid;
  pk_inst_t parent;
  pk_name_t name[PK_PROC_NAME_LENGTH];
  pk_name_t file[FILE_PATH_LENGTH];
} pk_proc;

// definition of a process handler
class pk_proc_h {
private:
  pk_name_t conf[FILE_PATH_LENGTH];
  // check_pk_proc_instance(name, file);

  // int start_pk_proc(__pk_proc* pkp);
  // int stop_pk_proc();
  // int restart_pk_proc();
  // int status_pk_proc();
public:
  pk_proc_h(pk_proc_options *ppo);
};

#endif
