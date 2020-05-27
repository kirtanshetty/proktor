#ifndef __PK_SRC_COMMON_H__
#define __PK_SRC_COMMON_H__

#include <stdlib.h>
#include <stdint.h>

#define VERSION 0

#define FILE_PATH_LENGTH 192
#define PK_PROC_NAME_LENGTH 32
#define PK_PROC_FILE_HASH_SIZE MD5_DIGEST_LENGTH

typedef uint16_t pk_inst_t;
typedef uint16_t pk_act_t;
typedef char pk_name_t;

typedef enum {
  AC_NONE,
  AC_START,
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
void get_md5_hash(unsigned char* hash, uint8_t* buf, uint32_t size);
bool is_md5_hash_eq(unsigned char* hash1, unsigned char* hash2);

#endif
