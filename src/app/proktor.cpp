#include <iostream>
#include <unistd.h>

#include <log.h>
#include <proktor.h>
#include <validate.h>
#include <logger.h>

void help_menu(){
  LOG(L_MSG) << LINE_DIVISION;
  LOG(L_MSG) << "Help menu";
  LOG(L_MSG) << LINE_DIVISION;
  LOG(L_MSG) << "Usage:";
  LOG(L_MSG) << "a - action";
  LOG(L_MSG) << "f - program file path";
  LOG(L_MSG) << "h - help menu";
  LOG(L_MSG) << LINE_DIVISION;
}

void invalid_option(char opt){
  LOG(L_ERR) << "invalid option:\n" << opt;
}

void invalid_option_value(char opt, char* val = NULL){
  if(val == NULL)
    LOG(L_ERR) << "option \"" << opt << "\" needs a value";
  else
    LOG(L_ERR) << "invalid value \"" << val << "\" for option \""<< opt <<"\".";
}

void init_options(int count, char** args, pk_proc_options* ppo){
  FBEG;
  int opt;

  const char* pp = getenv("PROKTOR_PATH");
  const char* pplp = getenv("PROKTOR_PROCESS_LOG_PATH");

  if(pp == NULL || pplp == NULL)
    exit_process(0, "(PROKTOR_LOG_PATH|PROKTOR_PROCESS_LOG_PATH) environment variable missing. They should be a valid directory path.");

  if(!vaild_dir_path((char*)pp) || !vaild_dir_path((char*)pplp))
    exit_process(0, "invalid (PROKTOR_LOG_PATH|PROKTOR_PROCESS_LOG_PATH) value. Directory with write access needed for application files.");

  strcpy(ppo->pk_log_path, pp);
  strcpy(ppo->pk_proc_log_path, pplp);

  LOG(L_DBG) << "PROKTOR_LOG_PATH: " << pp;
  LOG(L_DBG) << "PROKTOR_PROCESS_LOG_PATH: " << pplp;

  while((opt = getopt(count, args, ":ha:f:n:e:")) != -1){
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

  FEND;
}

int main(int argc, char **argv){
  pk_proc_options ppo;
  init_options(argc, argv, &ppo);
  run_proc_h(&ppo);
  return 0;
}