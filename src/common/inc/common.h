#ifndef __PK_SRC_COMMON_H__
#define __PK_SRC_COMMON_H__

#include <stdlib.h>
#include <stdint.h>

#define FILE_PATH_LENGTH 192
#define PK_PROC_NAME_LENGTH 32

typedef uint16_t pk_inst_t;
typedef char pk_name_t;

typedef enum {
  AC_START = 1,
  AC_STOP,
  AC_RESTART,
  AC_STATUS
} pk_proc_action_vals;

// options accepted by the process handler
typedef struct __pk_proc_options{
  pk_proc_action_vals action;
  pk_inst_t iid;
  pk_name_t pk_proc_name[PK_PROC_NAME_LENGTH];
  pk_name_t pk_path[FILE_PATH_LENGTH];
  pk_name_t pk_log_path[FILE_PATH_LENGTH];
  pk_name_t file_path[FILE_PATH_LENGTH];
  pk_name_t bin_path[FILE_PATH_LENGTH];
} pk_proc_options;

void exit_process(int code, const char* msg = NULL);

#endif
