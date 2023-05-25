// SFML Dev C++ 教學網站:https://programming727.pixnet.net/blog/post/24516428
// SFML 使用技巧1:https://www.twblogs.net/a/5e5021e8bd9eee101e86c2e8
// SFML 使用技巧2:https://blog.csdn.net/qq_33567644/article/details/100064135
// SFML 資料庫:https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php
// draw.io 程式的流程圖
// Flappy bird
// 程式範例:https://terminalroot.com/how-to-make-flappy-bird-with-cpp/
// 目前的圖片放在image裡面 若要執行檔案請將圖片放置在程式主體中的資料夾

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf; //使用SFML套件時 無須在前面寫sf::
using namespace std;

//碰撞:前四個是鳥的，後四個是pipe的，鳥和水管長寬都要慢慢測，回傳true則gameover
//回復備註:鳥用、水管取矩形，可以使用精靈.getGlobalBounds()取得全部圖形的矩形 類別Rect的intersects (const Rect< T > &rectangle) const 可以偵測是否跟鳥的矩形有碰撞 

/*void sf：：Window：：setKeyRepeatEnabled	(bool)	
啟用或禁用自動按鍵重複。

如果啟用了按鍵重複，您將在按住某個鍵的同時收到重複的按鍵事件。如果禁用，則在按下該鍵時只會收到一個事件。

默認情況下，按鍵重複處於啟用狀態。

參數
啟用	如果為 true，則啟用，如果為 false，則禁用

也就是按下空白時只偵測那一下
*/


flappyBird::flappyBird() { //建構元 初始化資料
	run();
	/*
    RenderWindow window(VideoMode(1000, 600),"111_2NIUFlappy Bird"); //宣告window物件寬1000，高600
    //window.setKeyRepeatEnabled(false); //禁止按住按鍵的連續觸發
    window.setPosition(Vector2i(0, 0));     //設定窗口的左上座標為(0,0)
    window.setFramerateLimit(60);           //設定最大幀數60
    font.loadFromFile("./AllSundries/font/flappybird.ttf");    //載入字體
    bg.loadFromFile("./AllSundries/image/background.png"); //載入背景圖片
    bd.loadFromFile("./AllSundries/image/bird.png");
    pi.loadFromFile("./AllSundries/image/pipe.png");
    state = homepage;
    background.setTexture(bg);
    released = true;
    */
}

void flappyBird::draw(vector<Sprite> allshow){
    //畫面更新的函數
    /*window.clear(Color::Black);//將畫面清除後設為黑色
    window.draw(background);//輸出的背景
    for(auto &something:allshow){//顯示所有的精靈
        window.draw(something);
    }
    window->display();//結束當前幀數*/
}
void flappyBird::show(State state){
    vector<Sprite> allshow;//利用vector 加入需要顯示的精靈
    if(state==homepage){
        //allshow.push_back(bird);//我們可能可以加入一隻鳥在中間上下飛
        //allshow.push_back(/*bottom1~3*/);//顯示三個按鈕
    }
    else if(state==game){
        //input name function
        /*if(name[0]==" "){
            //重新輸入name
        }*/
        //Call inGame();
        /*for(auto &p : pipes){
            window.draw(p);
        }
        window.draw(bird);
        if( gameover ){
            window.draw( text_gameover );
        }*/
    }
    else if(state==level){
        //show the 1st~10 name & score
    }
    else if(state==introduction){
        //show the introduction & all the team member
    }
    allshow.clear();
}
void flappyBird::run(){
	RenderWindow window(VideoMode(1000, 600),"111_2NIUFlappy Bird");
	window.setPosition(Vector2i(0, 0)); 
	window.setFramerateLimit(60); 
	bg.loadFromFile("./AllSundries/image/background.png"); //載入背景圖片
    background.setTexture(bg); 
    while(window.isOpen()){
    	while(window.pollEvent(event)){
			if(event.type==Event::Closed)
				window.close();
		}
    	window.clear();
		window.draw(background);
		window.display();
	}
	
	
}
