#include <iostream>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  printf("started test process\n");

  while(true){
    printf("this is test process.\n");
    sleep(1);
  }

  return 0;
}