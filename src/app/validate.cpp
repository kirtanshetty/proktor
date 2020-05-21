#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include <proktor.h>
#include <validate.h>

int8_t get_vaild_action(char* action){
  for(int i = 0; i < pkpa_map_length; i++){
    if(!strcmp(pkpa_map[i].action, action)){
      return pkpa_map[i].id;
    }
  }

  return -1;
}

bool vaild_file_path(char* path){
  return true;
  if(access(path, W_OK) != -1){
    return true;
  }

  return false;
}

bool vaild_dir_path(char* path){
  struct stat file;

  if (stat(path, &file) < 0){
    return false;
  }

  if (!S_ISDIR(file.st_mode)){
    return false;
  };

  return true;
}

bool vaild_pk_proc_name(char* name){
  return true;
}

bool valid_integer(char* input){
  while(*input){
    if(!isdigit(*input))
      return false;
    input++;
  }

  return true;
}
