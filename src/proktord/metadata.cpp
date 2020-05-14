#include <fcntl.h>
#include <metadata.h>
#include <common.h>

void dump_proc_list(const char* path, proc_list_buf* _plb){
  FILE* pFile = fopen(path, "w");
  fwrite(_plb->buf, ((_plb->list->length * sizeof(pk_proc_list)) + sizeof(pk_proc_list_size)), 1, pFile);

  free(_plb);
  _plb = NULL;
  // int fd = open(PK_METADATA_FILE, O_CREAT);
  // flock(fd, LOCK_EX);

  // unlink(lockfile);
  // flock(fd, LOCK_UN);
}

void get_proc_list(const char* path, proc_list_buf* _plb){
  struct stat st;
  if(stat(path, &st) == 0){
    size_t size = st.st_size;
    _plb->buf = (uint8_t*)malloc(sizeof(uint8_t) * size);

    if(!_plb->buf)
      exit_process(1, "get_process_list:memory allocation for the list failed");

    FILE* f = fopen(path, "rb");
    size_t n = fread(_plb->buf, size, 1, f);

    if(n != size)
      exit_process(1, "get_process_list:file read size mismatch");


  }
  else{
    LOG(L_MSG) << "get_process_list: file stat issue for " << path;
  }
}