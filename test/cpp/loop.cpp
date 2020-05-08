#include <iostream>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  // setvbuf(stdout, NULL, _IONBF, 0);
  printf("pf: started test process\n");
  // std::cout << "co: started test process" << std::endl;
  uint32_t timer = 1;

  while(true){
    // std::cout << "co: tick tick " << timer++ << std::endl;
    printf("pf: tick tick %u\n", timer++);
    // fflush(stdout);
    sleep(1);
  }

  return 0;
}
