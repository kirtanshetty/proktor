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
      exit_process(1, "get_process_list:memory allocation for the map failed");

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
  fwrite(_plb->buf, ((_plb->map->len * sizeof(pk_proc)) + sizeof(pk_proc_list_len_t)), 1, pFile);

  FEND;
  // int fd = open(PK_METADATA_FILE, O_CREAT);
  // flock(fd, LOCK_EX);

  // unlink(lockfile);
  // flock(fd, LOCK_UN);
}

void add_proc_to_list(pk_proc* new_proc, proc_list_buf* _plb){
  FBEG;

  uint32_t pk_proc_buf_size = 0, old_buf_size = 0;

  if(_plb->map){
    old_buf_size = (_plb->map->len * sizeof(pk_proc)) + PK_PROC_FILE_HEADER_SIZE;
    pk_proc_buf_size = old_buf_size + sizeof(pk_proc);
  }
  else
    pk_proc_buf_size = sizeof(pk_proc) + PK_PROC_FILE_HEADER_SIZE;

  printf("sizeof(pk_proc) %u, sizeof(pk_proc_file_map) %u\n", sizeof(pk_proc), sizeof(pk_proc_file_map));
  printf("pk_proc_buf_size %u, old_buf_size %u\n", pk_proc_buf_size, old_buf_size);

  uint8_t* new_buf = (uint8_t*)malloc(pk_proc_buf_size);
  memset(new_buf, 0, pk_proc_buf_size);

  if(_plb->buf){
    memcpy(new_buf, _plb->buf, old_buf_size);
    memcpy(new_buf + old_buf_size, new_proc, sizeof(pk_proc));

  }
  else{
    printf("single entry\n");
    memcpy(new_buf + PK_PROC_FILE_HEADER_SIZE, new_proc, sizeof(pk_proc));
  }

  _plb->buf = new_buf;
  _plb->map->len += 1;

  FEND;
}

void get_iid_for_proc(pk_proc* new_proc, pk_proc_file_map* map){
  if(!map){
    new_proc->iid = 1;
    return;
  }

  bool is_file = strlen(new_proc->file) ? true : false;
  new_proc->iid = 0;

  for(uint32_t i = 0; i < map->len; i++){
    if(!strcmp(new_proc->binary, map->list[i].binary)){
      if(is_file && strcmp(new_proc->file, map->list[i].file))
        continue;

      if(new_proc->iid < map->list[i].iid)
        new_proc->iid = map->list[i].iid;
    }
  }

  new_proc->iid += 1;
}

void get_uuid_for_proc(pk_proc* new_proc, pk_proc_file_map* map){
  if(!map){
    new_proc->uuid = 1;
    return;
  }

  new_proc->uuid = 0;
  pk_proc_uuid_t max_uuid = ~0;
  bool dup = false;

  for(uint32_t u = 0; u < max_uuid; u++){
    dup = false;
    for(uint32_t i = 0; i < map->len; i++){
      if(u == map->list[i].uuid){
        dup = true;
        break;
      }
    }

    if(!dup){
      new_proc->uuid = u;
      break;
    }
  }
}

bool is_used_instance_id(pk_proc* new_proc, pk_proc_file_map* map){
  if(!map) return false;

  bool is_file = strlen(new_proc->file) ? true : false;

  for(uint32_t i = 0; i < map->len; i++){
    if(!strcmp(new_proc->binary, map->list[i].binary)){
      if(is_file && strcmp(new_proc->file, map->list[i].file))
        continue;

      if(new_proc->iid == map->list[i].iid)
        return true;
    }
  }

  return false;
}

void print_proc_list(pk_proc_file_map* map){
  if(!map || !map->len){
    fprintf(stdout, "no list :(\n");
    return;
  }

  fprintf(stdout, "Proktor process map table. map size = %u\n", map->len);

  fprintf(stdout, "map->list[0].uuid = %p\n", &map->list[0].uuid);
  fprintf(stdout, "map->list[0].st = %p\n", &map->list[0].st);
  fprintf(stdout, "map->list[0].iid = %p\n", &map->list[0].iid);
  fprintf(stdout, "map->list[0].pid = %p\n", &map->list[0].pid);
  fprintf(stdout, "map->list[0].pid = %u\n", map->list[0].pid);
  fprintf(stdout, "map->list[0].m_pid = %p\n", &map->list[0].m_pid);
  fprintf(stdout, "map->list[0].m_pid = %u\n", map->list[0].m_pid);
  fprintf(stdout, "map->list[0].name = %p\n", &map->list[0].name);
  fprintf(stdout, "map->list[0].name = %s\n", map->list[0].name);



  fprintf(stdout, "%s %10s %15s %15s %8s %24s %9s %27s\n", "UUID", "STATE", "PID", "MID", "NAME", "IID", "BIN", "FILE");
  fprintf(stdout, "---------------------------------------------------------------------------------------\n");

  for(uint32_t i = 0; i < map->len; i++){
    fprintf(stdout, "%u", map->list[i].uuid);
    fprintf(stdout, "%10u", map->list[i].st);
    fprintf(stdout, "%15u", map->list[i].pid);
    fprintf(stdout, "%15u", map->list[i].m_pid);
    fprintf(stdout, "%20s", map->list[i].name);
    fprintf(stdout, "%10u", map->list[i].iid);
    fprintf(stdout, "%20s", map->list[i].binary);
    fprintf(stdout, "%20s\n", strlen(map->list[i].file) ? map->list[i].file : "NULL");
  }
}
