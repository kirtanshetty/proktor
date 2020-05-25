#ifndef __SRC_PK_METADATA_H__
#define __SRC_PK_METADATA_H__

#include <proc.h>

#define PK_METADATA_FILE "proktor_proc.md"

typedef union __proc_list_buf {
  uint8_t* buf;
  pk_proc_file_map* map;
} proc_list_buf;

void init_proc_list(char* path, proc_list_buf* _plb);
void deinit_proc_list(proc_list_buf* _plb);
void commit_proc_list(char* path, proc_list_buf* _plb);

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb);
void get_uuid_for_proc(pk_proc* new_proc, pk_proc_file_map* map);
void get_iid_for_proc(pk_proc* new_proc, pk_proc_file_map* map);
bool is_used_instance_id(pk_proc* new_proc, pk_proc_file_map* map);
void print_proc_list(pk_proc_file_map* map);

#endif
