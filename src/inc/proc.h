#ifndef __PK_SRC_PROC_H__
#define __PK_SRC_PROC_H__

#include <common.h>

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
  pk_name_t pk_log_path[FILE_PATH_LENGTH];
  pk_name_t pk_proc_log_path[FILE_PATH_LENGTH];
  pk_name_t file_path[FILE_PATH_LENGTH];
  pk_name_t bin_path[FILE_PATH_LENGTH];
} pk_proc_options;

typedef struct __pk_mon {
  pid_t pid;
  pk_name_t log[FILE_PATH_LENGTH];
} pk_mon;

// definition of a process
typedef struct __pk_proc {
  pid_t pid;
  pid_t m_pid;
  pk_inst_t iid;
  pk_name_t name[PK_PROC_NAME_LENGTH];
  pk_name_t file[FILE_PATH_LENGTH];
  pk_name_t binary[FILE_PATH_LENGTH];
  pk_name_t log[FILE_PATH_LENGTH];
} pk_proc;

// definition of a process handler
class pk_proc_h {
private:
  pk_proc_action_vals action;
  pk_proc pkp;
  pk_mon pkm;

public:
  pk_proc_h(pk_proc_options *ppo);
  void run();
};

#endif
