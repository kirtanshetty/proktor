#ifndef __PK_SRC_COMMON_H__
#define __PK_SRC_COMMON_H__

#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#define FILE_PATH_LENGTH 192
#define PK_PROC_NAME_LENGTH 32

#define PK_PROC_NAME_TAG "proktor_"
#define PK_MON_LOG_FILE "proktor.out"

void exit_process(int code, const char* msg = NULL);
void get_pk_proc_name_from_path(char* path, char* dest);
void get_pk_mon_log_file(char* path, char* dest);

#endif
