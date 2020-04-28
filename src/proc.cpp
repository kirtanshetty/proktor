#include <string.h>

#include "inc/proc.h"

pk_proc::pk_proc(char* _name){
  memset(name, 0, PK_PROC_NAME_LENGTH);
  strcpy(name, (char*)_name);
}

pk_proc_h::pk_proc_h(pk_proc_options *ppo){
  printf("pk_proc_h::pk_proc_h\n");
}

int pk_proc_h::start_pk_proc(){
  printf("pk_proc_h::start_pk_proc\n");
}

int pk_proc_h::stop_pk_proc(){
  printf("pk_proc_h::stop_pk_proc\n");
}

int pk_proc_h::restart_pk_proc(){
  printf("pk_proc_h::restart_pk_proc\n");
}