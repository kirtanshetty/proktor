#include <log.h>
#include <common.h>
#include <proc.h>
#include <metadata.h>
#include <action_handler.h>

// const char* pk_proc_name = PK_PROC_NAME_TAG;
// const char* pk_mon_file = PK_MON_LOG_FILE

void exit_process(int code, const char* msg){
  if(msg){
    LOG(L_FAT) << "Exit message: " << msg;
  }
  LOG(L_FAT) << "Exiting proktor.";
  exit(code);
}
