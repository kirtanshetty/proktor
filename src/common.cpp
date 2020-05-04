#include <log.h>
#include <common.h>

// const char* pk_proc_name = PK_PROC_NAME_TAG;
// const char* pk_mon_file = PK_MON_LOG_FILE

void exit_process(int code, const char* msg){
  if(msg){
    LOG(L_ERR) << "Exit message: " << msg;
  }
  LOG(L_ERR) << "Exiting proktor.";
  exit(code);
}

uint8_t __add_pk_proc_tag(char* name, uint8_t index, const char* pk_proc_tag){
  int i;
  for(i = index; i < (strlen(pk_proc_tag) + index); i++)
    name[i] = pk_proc_tag[i - index];

  return i;
}

int16_t __last_slash_index(char* path){
  int slash_index, path_length = strlen(path);

  for(slash_index = path_length - 1; slash_index >= 0; slash_index--){
    if(path[slash_index] == '/')
      break;
  }

  return slash_index;
}

void get_pk_proc_name_from_path(char* path, char* dest){
  int16_t slash_index, path_length = strlen(path);

  slash_index = __last_slash_index(path);

  uint8_t end = __add_pk_proc_tag(dest, 0, PK_PROC_NAME_TAG);
  for(int i = 0; i < (path_length - slash_index); i++){
    dest[i + end] = path[slash_index + i + 1];
  }
}

void get_pk_log_file(char* path, char* dest, const char* tag){
  int path_length = strlen(path);

  strcpy(dest, path);
  dest[path_length] = '/';

  __add_pk_proc_tag(dest, path_length + 1, tag);
}

bool pk_proc_restart(int stat){
  int length = sizeof(VALID_EXIT_SIGNALS)/sizeof(VALID_EXIT_SIGNALS[0]);

  for(int i = 0; i < length; i++)
    if(stat == VALID_EXIT_SIGNALS[i]) return false;

  return true;
}
