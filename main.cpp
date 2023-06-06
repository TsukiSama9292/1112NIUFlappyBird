#include "flappy.h"
using namespace std;
int main(){
  srand(time(NULL)); //設定隨機變數種子 
  auto *flappybird = new FlappyBird(); //建立flappy物件，即執行遊戲 
  delete(flappybird);//刪除物件 
  return 0;
}

