#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include <log.h>
#include <metadata.h>
#include <common.h>

void init_proc_list(char* path, proc_list_buf* _plb){
  FBEG;
  struct stat st;

  if(stat(path, &st) == 0){
    size_t size = st.st_size;
    _plb->buf = (uint8_t*)malloc(sizeof(uint8_t) * size);

    if(!_plb->buf)
      exit_process(1, "get_process_list:memory allocation for the list failed");

    FILE* f = fopen(path, "rb");
    size_t n = fread(_plb->buf, 1, size, f);

    if(n != size)
      exit_process(1, "get_process_list:file read size mismatch (possible corruption)");
  }
  else{
    LOG(L_MSG) << "get_process_list: file stat issue for " << path;
  }
  FEND;
}

void deinit_proc_list(proc_list_buf* _plb){
  free(_plb->buf);
  _plb = NULL;
}

void commit_proc_list(char* path, proc_list_buf* _plb){
  FBEG;

  FILE* pFile = fopen(path, "w");
  fwrite(_plb->buf, ((_plb->list->length * sizeof(pk_proc)) + sizeof(pk_proc_list_len_t)), 1, pFile);

  FEND;
  // int fd = open(PK_METADATA_FILE, O_CREAT);
  // flock(fd, LOCK_EX);

  // unlink(lockfile);
  // flock(fd, LOCK_UN);
}

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb){
  FBEG;

  uint32_t pk_proc_buf_size = 0, old_buf_size = 0;

  if(_plb->list){
    old_buf_size = (_plb->list->length * sizeof(pk_proc)) + sizeof(pk_proc_list_len_t);
    pk_proc_buf_size = old_buf_size + sizeof(pk_proc);
  }
  else
    pk_proc_buf_size = sizeof(pk_proc) + sizeof(pk_proc_list_len_t);

  uint8_t* new_buf = (uint8_t*)malloc(pk_proc_buf_size);
  memset(new_buf, 0, pk_proc_buf_size);

  if(_plb->buf){
    memcpy(new_buf, _plb->buf, old_buf_size);
    memcpy(new_buf + old_buf_size, new_proc, sizeof(pk_proc));

  }
  else
    memcpy(new_buf + sizeof(pk_proc_list_len_t), new_proc, sizeof(pk_proc));

  _plb->buf = new_buf;
  _plb->list->length += 1;

  FEND;
}

void get_instance_id_for_proc(pk_proc* new_proc, proc_list_buf* _plb){
  FBEG;

  bool is_file = strlen(new_proc->file) ? true : false;
  new_proc->iid = 0;

  for(uint32_t i = 0; i < _plb->list->length; i++){
    if(!strcmp(new_proc->binary, _plb->list->entries[i].binary)){
      if(is_file && strcmp(new_proc->file, _plb->list->entries[i].file))
        continue;

      if(new_proc->iid < _plb->list->entries[i].iid)
        new_proc->iid = _plb->list->entries[i].iid;
    }
  }

  new_proc->iid += 1;

  FEND;
}

bool is_used_instance_id(proc_list_buf* _plb){
  return true;
}

void print_proc_list(proc_list_buf* _plb){
  fprintf(stdout, "Proktor process list table. List size = %u\n", _plb->list->length);
  fprintf(stdout, "%s %5s %8s %24s %9s %27s\n", "PID", "MID", "NAME", "IID", "BIN", "FILE");
  fprintf(stdout, "---------------------------------------------------------------------------------------\n");
  if(_plb->list->length){
    for(uint32_t i = 0; i < _plb->list->length; i++){
      fprintf(stdout, "%u", _plb->list->entries[i].pid);
      fprintf(stdout, "%10u", _plb->list->entries[i].m_pid);
      fprintf(stdout, "%20s", _plb->list->entries[i].name);
      fprintf(stdout, "%10u", _plb->list->entries[i].iid);
      fprintf(stdout, "%20s", _plb->list->entries[i].binary);
      fprintf(stdout, "%20s\n", strlen(_plb->list->entries[i].file) ? _plb->list->entries[i].file : "NULL");
    }
  }
  else{
    fprintf(stdout, "no entries :(\n");
  }
}
