#include "flappy.h"
#include "flappy.cpp"
using namespace std;
int main(){
    srand(time(NULL));
    flappyBird *flappy = new flappyBird();
    flappy->run();
    return 0;
}
