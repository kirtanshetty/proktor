#ifndef __PK_SRC_PROC_H__
#define __PK_SRC_PROC_H__

#include <openssl/md5.h>

#include <common.h>

#define PK_PROC_NAME_TAG "proktor:"
#define PK_MON_LOG_FILE "proktor.out"

typedef uint32_t pk_proc_list_len_t;
typedef uint16_t pk_proc_list_ver_t;

typedef uint16_t pk_proc_stat_t;
typedef uint32_t pk_proc_uuid_t;

typedef enum {
  ST_UNAVAILABLE,
  ST_RUNNING,
  ST_KILLED,
  ST_STOPPED
} pk_proc_status;

typedef struct __pk_mon {
  pid_t pid;
  pk_name_t log[FILE_PATH_LENGTH];
  pk_name_t pk_md[FILE_PATH_LENGTH];
} pk_mon;

// definition of a process
typedef struct __pk_proc {
  pk_proc_uuid_t uuid;

  pk_proc_stat_t st;
  pk_inst_t iid;

  pid_t pid;
  pid_t m_pid;

  pk_name_t name[PK_PROC_NAME_LENGTH];
  pk_name_t file[FILE_PATH_LENGTH];
  pk_name_t binary[FILE_PATH_LENGTH];
  pk_name_t log[FILE_PATH_LENGTH];
} pk_proc;

#define PK_PROC_FILE_HEADER_SIZE 8 + PK_PROC_FILE_HASH_SIZE

typedef struct __pk_proc_file_map {
  unsigned char hash[PK_PROC_FILE_HASH_SIZE];
  uint16_t reserved;
  pk_proc_list_ver_t ver = VERSION;
  pk_proc_list_len_t len;

  pk_proc list[];
} pk_proc_file_map;

#endif
