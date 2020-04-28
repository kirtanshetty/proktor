#include "common.h"

#define PK_PROC_NAME_LENGTH 16
#define FILE_PATH_LENGTH 192

typedef uint8_t pk_inst_t;
typedef char pk_name_t;

typedef enum {
  ST_UNAVAILABLE,
  ST_RUNNING,
  ST_STOPPED
} pk_proc_status;

typedef enum {
  AC_START,
  AC_STOP,
  AC_RESTART,
  AC_STATUS
} pk_proc_actions;

struct pk_proc_options{
  char name[PK_PROC_NAME_LENGTH];
  pk_proc_actions action;
};

// definition of a process
class pk_proc {
private:
  pid_t pid;

  pk_inst_t iid;
  pk_inst_t parent;
  pk_name_t name[PK_PROC_NAME_LENGTH];
  pk_name_t file[FILE_PATH_LENGTH];

public:
  pk_proc(char* _name);
};

// definition of a process handler
class pk_proc_h {
private:
  pk_name_t conf[FILE_PATH_LENGTH];

  // check_pk_proc_instance(name, file);

public:
  pk_proc_h(pk_proc_options *ppo);

  int start_pk_proc();
  int stop_pk_proc();
  int restart_pk_proc();
};
