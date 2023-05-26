#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
enum State{homepage,game,level,introduction}state; //宣告模式(0為首頁 1為遊戲 2為排行 3為介紹)
class flappyBird{
    RenderWindow window;    //宣告視窗
    bool gameover,addscore;
    int score;
    Text text_score,text_gameover;  //分數、遊戲結束之文字
    float gravity,frame; 
    Texture bg, bd, pi;    //宣告圖片
    Font font;    //宣告字體
    vector<Text>text;    //宣告文字vector
    Sprite *background=new Sprite();    //宣告圖片精靈
    Sprite *bird=new Sprite();  
    Sprite *pipeBottom=new Sprite();    
    Sprite *pipeTop=new Sprite();
    vector<Sprite>pipes; //宣告水管的vectof
    //vector<Sprite>other; //宣告與水管無關的精靈vector，用於快速輸出至畫面
    Event event;
    int gameframe;  //遊戲時的幀，可用在小鳥動態and水管移動 ex:

    //沒有要用物件但受類別保護的函數放在protected，要用物件且受物件保護放在private，外部呼叫的放在public
    private:     
    protected:
        void inGame();
        void show(State);
        void draw(vector<Sprite>);//圖像的改變
        void movePipes();//水管的向左移動
        void setAnimeBird();//鳥的動態
        void moveBird();//鳥的上下

    public:
    	flappyBird();//建構元
        void run();//執行遊戲的函數，真正使用的main呼叫
        void setSFML();//設定初始SFML套件之物件
};
