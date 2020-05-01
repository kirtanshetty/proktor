#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char** argv) {
  printf("argc %d\n", argc);

  if(argc > 1){
    printf("argv %s\n", argv[1]);
    char *args[]={ argv[1], NULL };
    execvp(args[0],args);
    return 0;
  }

  char *args[]={"./EXEC",NULL};
  execvp(args[0],args);
  printf("Ending-----");

  return 0;
}
