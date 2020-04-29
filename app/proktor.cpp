#include <iostream>

#include "inc/proktor.h"
#include "inc/validate.h"

void exit_process(int code, const char* msg = NULL){
  if(msg){
    printf("Exit message: %s\n", msg);
  }
  printf("Exiting proktor\n");
  exit(code);
}

void help_menu(){
  printf(LINE_DIVISION);
  printf("Help menu\n");
  printf(LINE_DIVISION);
  printf("Usage: \n");
  printf("a - action\n");
  printf("f - program file path\n");
  printf("h - help menu\n");
  printf(LINE_DIVISION);
}

void invalid_option(char opt){
  printf("invalid option: %c\n", opt);
}

void invalid_option_value(char opt, char* val = NULL){
  if(val == NULL){
    printf("option \"%c\" needs a value\n", opt);
  }
  else{
    printf("invalid value \"%s\" for option \"%c\".\n", val, opt);
  }
}

int main(int argc, char **argv){
  pk_proc_options ppo;

  int opt;
  while((opt = getopt(argc, argv, ":ha:f:n:")) != -1){
    switch(opt){
      case 'a':{
        int8_t act = get_vaild_action(optarg);
        if(act < 0){
          invalid_option_value(opt, optarg);
          exit_process(0);
        }
        ppo.action = (pk_proc_action_vals)act;
        break;
      }
      case 'f':{
        if(vaild_file_path(optarg))
          strcpy(ppo.bin_path, optarg);
        else
          exit_process(0, "invalid file path for option f.");
        break;
      }
      case 'h':
        help_menu();
        exit_process(0);
      case ':':
        invalid_option_value(optopt);
        break;
      case '?':
        invalid_option(optopt);
        break;
    }
  }

  pk_proc_h pkph(&ppo);

  return 0;
}