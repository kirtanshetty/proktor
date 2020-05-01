#include <iostream>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  printf("started test process\n");
  uint32_t timer = 1;

  while(true){
    printf("tick tick %u\n", timer++);
    sleep(1);
  }

  return 0;
}