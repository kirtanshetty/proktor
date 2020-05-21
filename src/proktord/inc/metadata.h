#ifndef __SRC_PK_METADATA_H__
#define __SRC_PK_METADATA_H__

#include <proc.h>

#define PK_METADATA_FILE "proktor_proc.md"

typedef union __proc_list_buf {
  uint8_t* buf;
  pk_proc_list* list;
} proc_list_buf;

void init_proc_list(char* path, proc_list_buf* _plb);
void deinit_proc_list(proc_list_buf* _plb);
void commit_proc_list(char* path, proc_list_buf* _plb);

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb);
void get_instance_id_for_proc(pk_proc* new_proc, proc_list_buf* _plb);
bool is_used_instance_id(proc_list_buf* _plb);
void print_proc_list(proc_list_buf* _plb);

#endif
