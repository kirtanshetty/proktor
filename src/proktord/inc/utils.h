#ifndef __SRC_RD_UTILS_H__
#define __SRC_RD_UTILS_H__

void get_pk_proc_name_from_path(char* path, char* dest, const char* tag);
void get_pk_file(char* path, char* dest, const char* tag);


int VALID_EXIT_SIGNALS[] = {
  0,  // Program exited after execution
  9   // SIGKILL
};

bool pk_proc_valid_exit(int stat);

#endif
