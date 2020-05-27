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

void get_md5_hash(unsigned char* hash, uint8_t* buf, uint32_t size){
  MD5_CTX md5_ctx;
  MD5_Init(&md5_ctx);
  MD5_Update(&md5_ctx, buf, size);
  MD5_Final(hash, &md5_ctx);
}

bool is_md5_hash_eq(unsigned char* hash1, unsigned char* hash2){
  for(int i = 0; i < PK_PROC_FILE_HASH_SIZE; i++)
    if(hash1[i] != hash2[i])
      return false;

  return true;
}
