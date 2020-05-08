#ifndef __PK_SRC_PROC_H__
#define __PK_SRC_PROC_H__

#include <common.h>

#define PK_PROC_NAME_TAG "proktor:"
#define PK_MON_LOG_FILE "proktor.out"

typedef enum {
  ST_UNAVAILABLE,
  ST_RUNNING,
  ST_STOPPED
} pk_proc_status;

typedef struct __pk_mon {
  pid_t pid;
  pk_name_t log[FILE_PATH_LENGTH];
  pk_name_t pk_md[FILE_PATH_LENGTH];
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

// list of processes
// typedef struct __pk_proc_list_meta {
//   uint32_t count;
// } pk_proc_list_meta;

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
