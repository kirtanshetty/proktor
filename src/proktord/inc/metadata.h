#ifndef __SRC_PK_METADATA_H__
#define __SRC_PK_METADATA_H__

#include <proc.h>

#define PK_METADATA_FILE "proktor_proc.md"

typedef union __proc_list_buf {
  uint8_t* buf;
  pk_proc_list* list;
} proc_list_buf;

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb);
void dump_proc_list(char* path, proc_list_buf* _plb);
void get_proc_list(char* path, proc_list_buf* _plb);

#endif
