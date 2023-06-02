#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
#define TEAMNAME "111_2 NO.5 TEAM - Flappy bird"
#define SOUND_HIT "./AllSundries/sound/hit.wav"
#define SOUND_ADD "./AllSundries/sound/add.wav"
#define SOUND_BGM "./AllSundries/sound/bgm.wav"
#define SOUND_WING "./AllSundries/sound/wing.wav"
#define BACKGROUND "./AllSundries/image/background.png"
#define BIRD "./AllSundries/image/bird.png"
#define PIPE "./AllSundries/image/pipe.png"
#define FONT "./AllSundries/font/flappybird.ttf"
FlappyBird::FlappyBird(){ //建構元(子)，設定初始值 
  setSFML(); //由於SFML套件的物件設定不可在建構子執行，所以另外呼叫函數 
}
void FlappyBird::setSFML(){ //用於設定初始值 
	//參數設定 
	g =  frame = 0.f; //設定初始重量、幀(用於設定鳥的圖示與傾角) 
	interval = 240.f; //設定管道區間 
	count = 0; //常數-用於生成管道
	bgm_times = 0; //設定背景音樂播放之正記數 
	gameover = addscore = false;  //結束、加分為否 
	score = 0;  //分數為0 
	
	//視窗設定 
	window = new RenderWindow(VideoMode(1000, 600),TEAMNAME); //視窗設定 
	window->setPosition(Vector2i(0, 0)); //初始化視窗座標左上角(0,0) 
	
	//調控遊戲速度 
	window->setFramerateLimit( 60 ); //限制最大幀數，由於它在內部使用 sf::sleep，其精度取決於底層操作系統，結果也可能有點不精確，
	//window->setFramerateLimit( 0 ); //無幀數限制，遊戲以最快的速度進行 
	
	/*以下是背景的圖與精靈設定*/
	if(!bg.loadFromFile(BACKGROUND))//載入圖片
		cout<<"Fail loading background.png"<<endl;   
	background = new Sprite(); //建立精靈
	background->setTexture(bg); //精靈圖案設為背景圖
	//無須設定位置與大小 初始位置為(0,0) 視窗與圖等大 
	
	/*以下是鳥的圖與精靈設定*/
	if(!bd.loadFromFile(BIRD))//載入圖片
		cout<<"Fail loading bird.png"<<endl;  
	bird = new Sprite(); //建立精靈 
	bird->setTexture(bd);  //精靈圖案設為鳥 
	bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //設定鳥的初始位置 
	bird->setScale(2.f, 2.f); //調整大小(比例)
	bird->setTextureRect(IntRect(0, 0, 34, 24)); //取用圖片中，最左側的鳥 
	
	/*以下是管道的圖與精靈設定*/
	if(!pipe.loadFromFile(PIPE))//載入圖片 
		cout<<"Fail loading pipe.png"<<endl;
	pipe.loadFromFile(PIPE); //載入圖片
	pipeBottom = new Sprite(); //建立精靈 
	pipeTop = new Sprite(); //建立精靈 
	pipeBottom->setTexture(pipe); //精靈圖案設為管道 
	pipeTop->setTexture(pipe); //精靈圖案設為管道 
	pipeBottom->setScale(1.5f, 1.5f); //調整大小(比例)
	pipeTop->setScale(1.5f, -1.5f); //調整大小(比例)，負數為顛倒 
	
	/*以下是遊戲結束的字體與文字設定*/
	if(!font.loadFromFile(FONT))//載入字型 
		cout<<"Fail loading flappybird.ttf"<<endl; 
	text_gameover.setFont(font); //套用字型 
	text_gameover.setString("Press SPACE to restart"); //文字內容設定 
	text_gameover.setPosition(200, 300); //位置設定 
	text_gameover.setCharacterSize(50); //字體大小設定 
	text_gameover.setOutlineThickness(3); //字體粗細設定 
	
	/*以下是分數的字體與文字設定*/
	text_score.setFont(font); //套用字型 
	text_score.setString(std::to_string(score)); //文字內容設定  
	text_score.setPosition(10.f, 10.f); //位置設定
	text_score.setCharacterSize(50); //字體大小設定
	text_score.setOutlineThickness(3); //字體粗細設定
	
	/*以下是音效設定*/
	if(!buffer_hit.loadFromFile(SOUND_HIT)) //載入音效_hit 
		cout<<"Fail loading hit.wav"<<endl; //載入失敗_hit 
	if(!buffer_wing.loadFromFile(SOUND_WING)) //載入音效_wing
		cout<<"Fail loading wing.wav"<<endl; //載入失敗_wing 
	if(!buffer_add.loadFromFile(SOUND_ADD)) //載入音效_add
		cout<<"Fail loading add.wav"<<endl;	//載入失敗_add
	if(!buffer_bgm.loadFromFile(SOUND_BGM)) //載入音效_bgm
		cout<<"Fail loading bgm.wav"<<endl; //載入失敗_bgm
	sound_hit.setBuffer(buffer_hit); //音效播放器設定_hit 
	sound_wing.setBuffer(buffer_wing); //音效播放器設定_wing
	sound_add.setBuffer(buffer_add); //音效播放器設定_add
	sound_bgm.setBuffer(buffer_bgm); //音效播放器設定_bgm
	sound_bgm.play(); //bgm音樂播放 
}

void FlappyBird::events(){ //用於關閉視窗，重新開始遊戲 
	auto e = new Event(); //視窗事件物件設定 
	while( window->pollEvent( *e ) ){ //事件發生時執行 
		if( e->type == Event::Closed){ //事件若為點擊關閉視窗 
			window->close(); //視窗物件關閉，即遊戲關閉 
		}
	}
	if(gameover && Keyboard::isKeyPressed(Keyboard::Space)){//遊戲結束時按下空白鍵，即可重新開始 
		score = 0; //初始化分數
		bgm_times=0;
		g =  frame = 0.f; //初始化重量、幀(用於設定鳥的圖示與傾角)
		text_score.setString(to_string(score)); //初始化分數文字內容 
		pipes.clear(); //管道全部清除
		bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //初始化鳥的座標 
		gameover = false; //設結束結束為否 
	}
}

void FlappyBird::draw(){ //刷新畫面，渲染並顯示圖示 
	window->clear(); //清除整個畫面，用於刷新畫面，達到動畫效果 
	window->draw(*background); //待執行顯示背景 
	window->draw(*bird); //待執行顯示鳥 
	for(auto &p:pipes){ //遍歷所有管道 
		window->draw(p); //待執行顯示管道 
	}
	if(gameover) //如果遊戲結束 
		window->draw(text_gameover); //待執行顯示遊戲結束 
	window->draw(text_score); //待執行顯示分數 
	window->display(); //呼叫OpenGL渲染完成後調用(對當前幀的所有待顯示圖像顯示在畫面上) 
}

void FlappyBird::pipeMove(){ //用於移動水管，與鳥的跳躍 

	if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //高度25禁止往上
		sound_wing.play(); //播放揮翅膀音效 
		bird->setRotation(-frame - 10.f); //旋轉稍微向上看 
		g = -8.f; //設定重量向下 
	}
	else
		bird->setRotation(frame - 10.f); //旋轉稍微向下看
	if( count % 150 == 0 ){ //每執行150次時 
		int pos = rand() % 335 + 25; //設定隨機高度 
		pipeTop->setPosition(1000, pos);  //上管道設定位置
		pipeBottom->setPosition(1000, pos + interval); //下管道設定位置 
		pipes.push_back(*pipeTop); //管道vector新增上管道 
		pipes.push_back(*pipeBottom); //管道vector新增下管道  
	}
	for (size_t i {}; i < pipes.size(); i++) { //利用size_t 遍歷物件  
		if(pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds())){ //生成管道、與鳥的矩形，如果兩矩形交疊，執行 
			/*/因為生成矩形會讓管道、鳥圖片以未旋轉的，但縮放過的矩形大小(透明也算)進行生成，導致些許大小落差 
			為了讓鳥看起來像是撞上去，所以讓它偷偷向前移動*/
			bird->move(15.f, 0); 
			if( pipes[i].getScale().y < 0 ) //如果(碰撞管道y軸的比例小於0，即是上管道)，執行 
				bird->move(0,-10.f); //稍微向上 
			else //若為下管道 
				bird->move(0,10.f); //稍微向下 
			gameover = true; //遊戲結束 
			sound_hit.play(); //播放撞擊音效 
		}
		if(pipes[i].getPosition().x < -150 ){ //管道的x軸在畫面左側150(超出畫面) 
			pipes.erase(pipes.begin() + i );  //清除管道 
		} 
		pipes[i].move(-4.f, 0); //管道向左移動 
		if(pipes[i].getPosition().x == 408 && !addscore ){ //當管道比鳥更靠左側，且還未加分 
			text_score.setString(to_string(++score)); //顯示分數增加 
			sound_add.play(); //播放加分音效  
			addscore = true; //設定已經加過分數了，避免上下管道都加分 
		}else //另一個管道通過，將其設定還未加過分數，使下次能繼續加分 
			addscore = false;
	}
}

void FlappyBird::birdAnime(){ //設定鳥的動畫 
	frame += 0.15f; // 設定幀 
	if( frame > 3 ){ // 當大於三
		frame -= 3; // 設為-3，製造循環的感覺 
	}	
	bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //設定圖示取樣範圍 
}

void FlappyBird::birdMove(){ //移動鳥 
	bird->move(0, g); //向下墜落 
	g += 0.5f; //逐漸增快 
	if(bird->getPosition().y>650){ //當整個鳥超出畫面(y>650) 
		sound_hit.play(); //播放撞擊音效  
		gameover = true; //遊戲結束 
	}
}

void FlappyBird::game(){ //執行精靈移動與鳥的跳躍和動畫 
	if(!gameover){ //還沒結束遊戲
		birdAnime(); //呼叫鳥的動畫 
		birdMove(); //呼叫鳥的位移 
		pipeMove(); //呼叫管道的位移 
	}
}

void FlappyBird::run(){ 
	while( window->isOpen() ){ //當視窗還開著
		
		events(); //呼叫函數events，用於關閉視窗，重新開始遊戲 
		game(); //呼叫函數game，執行精靈移動與鳥的跳躍和動畫 
		draw(); //呼叫函數draw，刷新畫面，渲染並顯示圖示
		count++; //常數增加，用於管道生成
		if( count == 300 ){ //常數等於300 
			count = 0; //常數重製
			bgmCircle(); //呼叫音樂重複播放 
		}
	}
}
void FlappyBird::bgmCircle(){ //音樂重複播放 
	if(bgm_times>=6){ //當count循環6次 重新播放bgm 
		bgm_times=0; //初始化bgm_times 
		sound_bgm.play(); //重新播放bgm 
	}else{
		bgm_times++; //記數+1 
	}
}

