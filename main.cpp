#include "set_rank.h"
#include "set_rank.cpp"
#include "flappy.h"
#include "flappy.cpp"
 
using namespace std;
int main(){
  srand(time(NULL));
  auto *flappybird = new FlappyBird();
  flappybird->run();
  return 0;
}

