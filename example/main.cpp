#include "flappy.h"
#include "flappy.cpp"

int main(){
  std::srand( std::time(0));
  auto *flappy = new FlappyBird();
  flappy->run();
  return 0;
}

