#include <iostream>
#include <unistd.h>

#include <log.h>
#include <proktor.h>
#include <validate.h>
#include <logger.h>
#include <pdc.h>

#define MANDATORY_STR "(Mandatory)"
#define LINE_BREAK "\n"

void help_menu(){
  fprintf(stdout, LINE_DIVISION LINE_BREAK);
  fprintf(stdout, "Help menu" LINE_BREAK);
  fprintf(stdout, LINE_DIVISION LINE_BREAK);
  fprintf(stdout, "Usage:" LINE_BREAK);
  fprintf(stdout, "a - action " MANDATORY_STR LINE_BREAK);
  fprintf(stdout, "f - program file path" LINE_BREAK);
  fprintf(stdout, "h - help menu" LINE_BREAK);
  fprintf(stdout, LINE_DIVISION LINE_BREAK);
}

void invalid_option(char opt){
  LOG(L_FAT) << "invalid option:\n" << opt;
}

void invalid_option_value(char opt, char* val = NULL){
  if(val == NULL)
    LOG(L_FAT) << "option \"" << opt << "\" needs a value";
  else
    LOG(L_FAT) << "invalid value \"" << val << "\" for option \""<< opt <<"\".";
}

bool mandatory_opt_check(pk_proc_options* ppo){
  if(!ppo->action) return false;

  return true;
}

void init_options(int count, char** args, pk_proc_options* ppo){
  FBEG;
  int opt;

  const char* pp = getenv("PROKTOR_PATH");
  const char* pplp = getenv("PROKTOR_PROCESS_LOG_PATH");

  if(pp == NULL || pplp == NULL)
    exit_process(0, "(PROKTOR_PATH|PROKTOR_PROCESS_LOG_PATH) environment variable missing. They should be a valid directory path.");

  if(!vaild_dir_path((char*)pp) || !vaild_dir_path((char*)pplp))
    exit_process(0, "invalid (PROKTOR_PATH|PROKTOR_PROCESS_LOG_PATH) value. Directory with write access needed for application files.");

  strcpy(ppo->pk_path, pp);
  strcpy(ppo->pk_log_path, pplp);

  LOG(L_DBG) << "PROKTOR_PATH: " << pp;
  LOG(L_DBG) << "PROKTOR_PROCESS_LOG_PATH: " << pplp;

  while((opt = getopt(count, args, ":ha:f:n:e:i:")) != -1){
    printf("while loop\n");
    printf("opt = %c\n", opt);
    switch(opt){
      case 'a':{
        int8_t act = get_vaild_action(optarg);
        if(act < 0){
          invalid_option_value(opt, optarg);
          exit_process(0);
        }
        ppo->action = (pk_proc_action_vals)act;

        break;
      }
      case 'f':{
        if(vaild_file_path(optarg))
          strcpy(ppo->file_path, optarg);
        else
          exit_process(0, "invalid file path for option -f.");

        break;
      }
      case 'n':{
        if(vaild_pk_proc_name(optarg))
          strcpy(ppo->pk_proc_name, optarg);
        else
          exit_process(0, "invalid proktor process name for option -n.");

        break;
      }
      case 'e':{
        if(vaild_file_path(optarg))
          strcpy(ppo->bin_path, optarg);
        else
          exit_process(0, "invalid binary path for option -e.");

        break;
      }
      case 'i':{
        if(valid_integer(optarg))
          ppo->iid = atoi(optarg);
        else
          exit_process(0, "invalid instance id for -i.");

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

  if(!mandatory_opt_check(ppo)){
    help_menu();
    exit_process(0, "mandatory options missing.");
  }

  FEND;
}

int main(int argc, char **argv){
  pk_proc_options ppo;

  memset(&ppo, 0, sizeof(pk_proc_options));
  init_options(argc, argv, &ppo);
  run_proc_h(&ppo);

  return 0;
}