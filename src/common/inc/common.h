#ifndef __PK_SRC_COMMON_H__
#define __PK_SRC_COMMON_H__

#include <stdint.h>

#define FILE_PATH_LENGTH 192
#define PK_PROC_NAME_LENGTH 32

typedef uint8_t pk_inst_t;
typedef char pk_name_t;

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

void exit_process(int code, const char* msg = NULL);
void get_pk_proc_name_from_path(char* path, char* dest, const char* tag);
void get_pk_file(char* path, char* dest, const char* tag);

int VALID_EXIT_SIGNALS[] = {
  0,  // Program exited after execution
  9   // SIGKILL
};

bool pk_proc_valid_exit(int stat);

#endif
