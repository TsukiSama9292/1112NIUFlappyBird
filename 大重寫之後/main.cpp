#include "set_rank.h"
#include "set_rank.cpp"
#include "flappy.h"

using namespace std;
int main(){
  srand(time(NULL));
  auto *flappybird = new FlappyBird();
  flappybird->changeWindow();
  return 0;
}

