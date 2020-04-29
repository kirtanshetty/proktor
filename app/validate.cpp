#include <iostream>

#include "inc/validate.h"

int8_t get_vaild_action(char* action){
  for(int i = 0; i < pkpa_map_length; i++){
    if(!strcmp(pkpa_map[i].action, action)){
      return pkpa_map[i].id;
    }
  }

  return -1;
}

bool vaild_file_path(char* path){
  if(access(path, F_OK) != -1){
    printf("file exists\n");
    return true;
  }

  return false;
}
