#include "flappy.h"
using namespace std;
int main(){
  srand(time(NULL));
  auto *flappybird = new FlappyBird(); //�إ�flappy����A�Y����C�� 
  delete(flappybird);//�R������ 
  return 0;
}

