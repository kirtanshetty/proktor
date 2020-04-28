#include <iostream>
#include <unistd.h>

#include "../src/inc/proc.h"
#include "inc/validate.h"

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

int main(int argc, char **argv){
  int opt;
  pk_proc_options ppo;

  while((opt = getopt(argc, argv, ":ha:f:")) != -1){
    switch(opt){
      case 'a':
        printf("action: %c %s\n", opt, optarg);
        break;
      case 'f':
        printf("filename: %c %s\n", opt, optarg);
        break;
      case 'h':
        help_menu();
        exit(0);
      case ':':
        printf("option \"%c\" needs a value\n", opt);
        break;
      case '?':
        printf("invalid option: %c\n", optopt);
        break;
    }
  }

  pk_proc pkp("abc");

  return 0;
}