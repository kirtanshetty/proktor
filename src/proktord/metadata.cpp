#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#include <log.h>
#include <metadata.h>
#include <common.h>

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb){
  FBEG;

  // uint32_t pk_proc_size = sizeof(pk_proc);
  printf("pk_proc_size %u\n", sizeof(pk_proc));

  uint32_t pk_proc_buf_size;
  printf("pk_proc_size %d\n", _plb->list);

  if(_plb->list){
    printf("if condition\n");
    pk_proc_buf_size = (_plb->list->length * sizeof(pk_proc)) + sizeof(pk_proc) + sizeof(pk_proc_list_size);
  }
  else{
    printf("else condition\n");
    pk_proc_buf_size = sizeof(pk_proc) + sizeof(pk_proc_list_size);
  }

  printf("pk_proc_buf_size %u\n", pk_proc_buf_size);

  // uint32_t total = pk_proc_buf_size + pk_proc_size;

  printf("total %u\n", pk_proc_buf_size);
  uint8_t* new_buf = (uint8_t*)malloc(pk_proc_buf_size);
  memset(new_buf, 0, pk_proc_buf_size);
  printf("2 %p , %p\n", new_buf, (new_buf + sizeof(pk_proc_list_size)));

  if(_plb->buf)
    memcpy(new_buf, _plb->buf, pk_proc_buf_size);
  else
    memcpy(new_buf + sizeof(pk_proc_list_size), new_proc, sizeof(pk_proc));

  printf("3 %u\n", (*(pid_t*)(new_buf + 2 + sizeof(pid_t))));
  _plb->buf = new_buf;
  printf("4 %u\n", sizeof(pid_t));
  _plb->list->length += 1;



  printf("_plb->buf _plb->buf %p\n", _plb->buf);
  printf("_plb->buf _plb->list %p\n", _plb->list);
  printf("_plb->buf &_plb->list->length %p\n", &_plb->list->length);
  printf("_plb->buf &_plb->list->entries %p\n", &_plb->list->entries);

  printf("_plb->buf m_pid %u\n", (*(pid_t*)(_plb->buf + 4 + sizeof(pid_t))));
  printf("_plb->list m_pid %u\n", (*(pid_t*)(_plb->list + 4 + sizeof(pid_t))));

  printf("_plb->buf iid %u\n", (*(pk_inst_t*)(_plb->buf + 4 + 4 + 4)));
  printf("_plb->buf name %s\n", (pk_name_t*)(_plb->buf + 4 + 4 + 4 + 2));
  printf("new_buf name %s\n", (pk_name_t*)(new_buf + 4 + 4 + 4 + 2));

  printf("---------------------------------------\n");

  printf("add_proc_to_list:_plb->list->length %u \n", _plb->list->length);
  printf("add_proc_to_list:_plb->list->entries[0].pid %u \n", _plb->list->entries[0].pid);
  printf("add_proc_to_list:_plb->list->entries[0].m_pid %u \n", _plb->list->entries[0].m_pid);
  printf("add_proc_to_list:_plb->list->entries[0].name %s \n", _plb->list->entries[0].name);

  // printf("3\n");
  // memcpy(new_buf + pk_proc_buf_size, new_proc, pk_proc_size);
  // printf("4\n");

  // free(_plb->buf);
  // printf("5\n");
  // _plb->buf = new_buf;
  // printf("6\n");
  // _plb->list->length += 1;

  FEND;
}

void dump_proc_list(char* path, proc_list_buf* _plb){
  FBEG;

  FILE* pFile = fopen(path, "w");
  fwrite(_plb->buf, ((_plb->list->length * sizeof(pk_proc)) + sizeof(pk_proc_list_size)), 1, pFile);

  free(_plb);
  _plb = NULL;

  FEND;
  // int fd = open(PK_METADATA_FILE, O_CREAT);
  // flock(fd, LOCK_EX);

  // unlink(lockfile);
  // flock(fd, LOCK_UN);
}

void get_proc_list(char* path, proc_list_buf* _plb){
  FBEG;
  struct stat st;
  printf("_plb %p\n", _plb);
  printf("_plb %p\n", &_plb->buf);

  if(stat(path, &st) == 0){
    size_t size = st.st_size;
    _plb->buf = (uint8_t*)malloc(sizeof(uint8_t) * size);

    if(!_plb->buf)
      exit_process(1, "get_process_list:memory allocation for the list failed");

    FILE* f = fopen(path, "rb");
    size_t n = fread(_plb->buf, size, 1, f);

    if(n != size)
      exit_process(1, "get_process_list:file read size mismatch (possible corruption)");
  }
  else{
    LOG(L_MSG) << "get_process_list: file stat issue for " << path;
  }
  FEND;
}