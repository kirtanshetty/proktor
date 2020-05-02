#include <log.h>
#include <common.h>

const char* pk_proc_tag = PK_PROC_NAME_TAG;

void exit_process(int code, const char* msg){
  if(msg){
    LOG(L_ERR) << "Exit message:" << msg;
  }
  LOG(L_ERR) << "Exiting proktor.";
  exit(code);
}

uint8_t __add_pk_proc_tag(char* name){
  int i;
  for(i = 0; i < strlen(pk_proc_tag); i++)
    name[i] = pk_proc_tag[i];

  return i;
}

void get_pk_proc_name_from_path(char* path, char* dest){
  int slash_index, path_length = strlen(path);
  for(slash_index = path_length - 1; slash_index >= 0; slash_index--){
    #ifdef _WIN32
    if(path[slash_index] == '\\')
    #else
    if(path[slash_index] == '/')
    #endif
      break;
  }

  uint8_t end = __add_pk_proc_tag(dest);
  for(int i = 0; i < (path_length - slash_index); i++){
    dest[i + end] = path[slash_index + i + 1];
  }
}
