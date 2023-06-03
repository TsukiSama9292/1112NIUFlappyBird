#include "flappy.h"
using namespace std;
int main(){
  srand(time(NULL));
  auto *flappybird = new FlappyBird();
  flappybird->flappy_start();
  return 0;
}

