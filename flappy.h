#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "set_rank.h"
#include "textbox.hpp"
#include "button.h" 
#define TEAMNAME "111_2 NO.5 TEAM - Flappy bird"
#define SOUND_HIT "./AllSundries/sound/hit.wav"
#define SOUND_ADD "./AllSundries/sound/add.wav"
#define SOUND_BGM "./AllSundries/sound/bgm.wav"
#define SOUND_WING "./AllSundries/sound/wing.wav"
#define SOUND_NO1 "./AllSundries/sound/no1.wav"
#define BACKGROUND "./AllSundries/image/background.png"
#define BIRD "./AllSundries/image/bird.png"
#define PIPE "./AllSundries/image/pipe.png"
#define TEAM_PICTURE "./AllSundries/image/team.png"
#define FONT "./AllSundries/font/flappybird.ttf"
#define BUTTON_Play "./AllSundries/button/play.png"
#define BUTTON_ENTER "./AllSundries/button/enter.png"
#define BUTTON_RESTART "./AllSundries/button/restart.png"
#define BUTTON_HOMEPAGE "./AllSundries/button/home.png"
#define BUTTON_SHOWRANK "./AllSundries/button/rank.png"
#define BUTTON_INTRODUCE "./AllSundries/button/intro.png"
//宜蘭大學 資工一 程式設計 第五組 期末專案 FlappyBird 之遊戲程式設計  
using namespace std;
using namespace sf;
enum Status{_homepage, _inputname, _game, _gameover, _showrank, _introduce};//遊戲狀態之enum 
class FlappyBird : private setrank{ //FlappyBird繼承setrank
	private:
	Event event;//宣告sf::事件 event 
	RenderWindow *window; //宣告sf::RenderWindow 指標變數 (動態記憶體) 
	float g,frame,interval; //宣告重力、幀(用於動畫)、間隔(管道的間隔) 
	int count,bgm_timing,rankfield,any_timing,now_rank;//常數(水管生成時機)、BGM時機(循環播放)、排行範圍(顯示的範圍)、其他時機(用於箭頭與空白按下變紅轉白)、目前排名 
	string name,showrank,str; //宣告名稱、顯示排行榜、str用於生成sf::Text物件與Class Button物件時使用 
	long long score; //宣告分數 
	pair<int,long long> now; //用於setrank之pair<int,long long> <目前排名,歷史最高分> 
	SoundBuffer buffer_hit,buffer_wing,buffer_add,buffer_bgm,buffer_no1; //宣告sf::SoundBuffer物件用於讀取音檔 
	Sound sound_hit,sound_wing,sound_add,sound_bgm,sound_no1; //宣告sf::Sound物件 音檔的播放器 
	Font font; //宣告sf::Font物件 讀取字體 
	Text text_score,text_rank,text_introduce,text_announce,arrow_up,arrow_down,ann_space; //宣告sf::Text 物件 用於文字顯示 
	Texture bg,bd,pipe,team;//宣告sf::Texture 物件 用於加載圖片紋理(之後用於設定精靈圖片) 
	Sprite *background,*bird,*pipeBottom,*pipeTop,*team_picture;//宣告 sf::Sprite 指標變數(動態記憶體) 用於圖像、圖像移動、圖像碰撞...
	vector<Sprite> pipes;//宣告 vector<sf::Sprite> 陣列 用於存放、刪除管道 
	bool gameover, addscore; //宣告bool 遊戲結束、加分 
	Status gamestatus = _homepage; //宣告enum Status 用於判斷遊戲當前運行狀態 
	Textbox *textbox1; //宣告 Class Textbox 指標變數(動態記憶體) 
	Button *button_play,*button_enter,*button_restart,*button_home,*button_rank,*button_intro; //宣告 Class Button 指標變數(動態記憶體)  
	void _showRank(){//setrank類別之應用_顯示排行榜(名次、名稱、分數) 
		showrank="";//顯示之文字 
		if(v.size()==0)//rank.txt無資料 
			showrank="No Data";//顯示No Data 
		for(int i=rankfield;i<v.size();i++){//遍歷vector v
			showrank+="NO."+to_string(renewrank(v[i]).first)+" "+v[i].first+" Score:"+to_string(v[i].second)+"\n";//顯示格式
			if(i==rankfield+6)//7人時停下 
				break;//跳出for迴圈 
		}
		text_rank.setString(showrank);//設定文字 
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,250-text_rank.getGlobalBounds().height/2.f);//設定位置 
	}
	void _gameOver(){ //遊戲結束之音效、狀態、當前名次顯示與歷史分數之顯示 
		sound_hit.play(); //播放撞擊音效
		gameover = true; //遊戲結束 
		gamestatus=_gameover; //狀態設定 
		now = renewrank({name,score}); //重製分數排行 
		now_rank=now.first; //目前的排行  
		text_rank.setString("NO."+to_string(now_rank)+" "+name+" Score:"+to_string(score)+" History:"+to_string(now.second)); //顯示格式 
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,187.5f);//設定位置 
		if(now.first==1 && score>=now.second){//如果目前是第一名且分數突破自己最高紀錄，暫停背景音樂，播放勝利音效 
			sound_bgm.stop();//暫停背景音樂 
			bgm_timing=1000;//設定背景音樂時間，用於下次循環 
			sound_no1.play();//播放勝利音樂 
		}		
	}
	void setSFML(){ //用於設定初始值
		//參數設定 
		name=""; //清空name
		g=frame=0.f; //預設首頁鳥向下、幀(用於設定鳥的圖示與傾角) 
		interval = 240.f; //設定管道區間 
		count = 0; //常數-用於生成管道
		bgm_timing = 0; //設定背景音樂播放之正記數 
		gameover = addscore = false;  //結束、加分為否 
		score = 0;  //分數為0
		rankfield=0; //排名顯示 初始為第一名在最上面 
		//視窗設定 
		window=new RenderWindow(VideoMode(1000, 600),TEAMNAME); //視窗設定 
		window->setPosition(Vector2i(0, 0)); //初始化視窗座標左上角(0,0) 
		window->setKeyRepeatEnabled(true); //可以按下按鈕，會重複判斷 
		//調控遊戲速度 
		window->setFramerateLimit( 60 ); //限制最大幀數，由於它在內部使用 sf::sleep，其精度取決於底層操作系統，結果也可能有點不精確，
		//window->setFramerateLimit( 0 ); //無幀數限制，遊戲以最快的速度進行 
		//textbox之應用 
		textbox1=new Textbox(40,Color::White,true);//字體40，白字 
		/*以下是背景的圖與精靈設定*/
		if(!bg.loadFromFile(BACKGROUND))//載入圖片
			cout<<"Fail loading background.png"<<endl;//報錯 
		background=new Sprite(); //建立精靈
		background->setTexture(bg); //精靈圖案設為背景圖
		//無須設定位置與大小 初始位置為(0,0) 視窗與圖等大 
		
		/*以下是鳥的圖與精靈設定*/
		if(!bd.loadFromFile(BIRD))//載入圖片
			cout<<"Fail loading bird.png"<<endl;  
		bird=new Sprite(); //建立精靈 
		setPictureSize(bird,&bd,2.5f,3,500,75);
		/*團隊照片*/
		if(!team.loadFromFile(TEAM_PICTURE))//載入圖片
			cout<<"Fail loading team_picture"<<endl;//報錯
		team_picture=new Sprite();//建立精靈
		team_picture->setTexture(team);//精靈圖案設為團隊照片 
		team_picture->setScale(0.24,0.24);//設定精靈(圖片)大小 
		team_picture->setPosition(500-team_picture->getGlobalBounds().width/2.f,350-team_picture->getGlobalBounds().height/2.f);//設定精靈(圖片)位置 
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
		
		if(!font.loadFromFile(FONT))//載入字型 
			cout<<"Fail loading flappybird.ttf"<<endl; 
		
		/*以下是字體與文字設定*/ 
		str=to_string(score);
		setTextSFML(&text_score,10.f,10.f,50,str);//分數字體與文字 
		str=""; 
		setTextSFML(&text_rank,10.f,250.f,50,str);//rank字體與文字 
		str="This Flappy Bird game is created by B1143007 Lee Min-Chen, B114\n3009 Wu Bing-Rong, B1143015 Lin Xuan-You, B1143021 Lin Cheng-Wei\n, B1143027 ChenBo-Hao, and B1143036 Huang Qi-Ting, is a simple \nbut addictive game. Guide the bird through pipes by tapping the \nscreen or pressing spacebar. Avoid collisions with pipes and \nthe ground. Score points for each successful passage. \nChallenge yourself with increasing difficulty. Aim for the \nhighest score and compete with friends.";
		setTextSFML(&text_introduce,10.f,10.f,30,str);//介紹字體與文字 
		str="Name : \nWarning : Only supports input of English,\nnumbers and some symbols";
		setTextSFML(&text_announce,100.f,100.f,40,str);//提示名稱輸入字體與文字 
		str="^";
		setTextSFML(&arrow_up,80.f,350.f,40,str);//向上箭頭字體與文字 
		setTextSFML(&arrow_down,80.f,425.f,40,str);//向下箭頭字體與文字 
		arrow_down.setScale(1.0f, -1.0f);//向下箭頭上下鏡向 
		str="SPACE";
		setTextSFML(&ann_space,10.f,550.f,40,str);
		/*以下是音效設定*/
		if(!buffer_hit.loadFromFile(SOUND_HIT)) //載入音效_hit 
			cout<<"Fail loading hit.wav"<<endl; //載入失敗_hit 
		if(!buffer_wing.loadFromFile(SOUND_WING)) //載入音效_wing
			cout<<"Fail loading wing.wav"<<endl; //載入失敗_wing 
		if(!buffer_add.loadFromFile(SOUND_ADD)) //載入音效_add
			cout<<"Fail loading add.wav"<<endl;	//載入失敗_add
		if(!buffer_bgm.loadFromFile(SOUND_BGM)) //載入音效_bgm
			cout<<"Fail loading bgm.wav"<<endl; //載入失敗_bgm
		if(!buffer_no1.loadFromFile(SOUND_NO1)) //載入音效_no1
			cout<<"Fail loading no1.wav"<<endl; //載入失敗_no1
		sound_hit.setBuffer(buffer_hit); //音效播放器設定_hit 
		sound_wing.setBuffer(buffer_wing); //音效播放器設定_wing
		sound_add.setBuffer(buffer_add); //音效播放器設定_add
		sound_bgm.setBuffer(buffer_bgm); //音效播放器設定_bgm 
		sound_no1.setBuffer(buffer_no1); //音效播放器設定_no1
				
		textbox1->setFont(font); //設定字體 
		textbox1->setPosition({240,100});  //textbox位置 
		textbox1->setLimit(true,15);  //設定是否設限and字數限制
		/*Button類別物件之測試*/
		str=BUTTON_Play; //str設為按鈕圖片位置 
		button_play=new Button(str,0.4f,500.f,250.f); //按鈕play物件設定(紋理、精靈、大小、位置) 
		str=BUTTON_ENTER; //str設為按鈕圖片位置  
		button_enter=new Button(str,0.4f,500.f,375.f); //按鈕enter物件設定(紋理、精靈、大小、位置)  
		str=BUTTON_RESTART; //str設為按鈕圖片位置  
		button_restart=new Button(str,0.4f,500.f,375.f); //按鈕restart物件設定(紋理、精靈、大小、位置)  
		str=BUTTON_SHOWRANK; //str設為按鈕圖片位置  
		button_rank=new Button(str,0.4f,500.f,375.f); //按鈕rank物件設定(紋理、精靈、大小、位置)  
		str=BUTTON_HOMEPAGE; //str設為按鈕圖片位置  
		button_home=new Button(str,0.4f,500.f,500.f); //按鈕home物件設定(紋理、精靈、大小、位置)  
		str=BUTTON_INTRODUCE; //str設為按鈕圖片位置  
		button_intro=new Button(str,0.4f,500.f,500.f); //按鈕intro物件設定(紋理、精靈、大小、位置)  
		changeWindow(); //呼叫視窗改變函數 
	}
	void setTextSFML(Text *text_show,float px,float py,int size,string str){//設定Text之格式與文字內容 
		text_show->setFont(font); //套用字型 
		text_show->setString(str); //文字內容設定  
		text_show->setPosition(px, py); //位置設定
		text_show->setCharacterSize(size); //字體大小設定
		text_show->setOutlineThickness(3); //字體粗細設定
	}	
	void setPictureSize(Sprite *spt,Texture *txt,float resize,float cut,float px,float py){//設定精靈之圖片、大小、位置 
		spt->setTexture(*txt);//圖片設定 
		spt->setScale(resize,resize);//大小(比例) 
		spt->setTextureRect(IntRect(0,0,txt->getSize().x/cut,txt->getSize().y));//取圖片特定範圍 
		spt->setPosition(px-spt->getGlobalBounds().width/2.f,py-spt->getGlobalBounds().height/2.f);//設定位置 
	}
	void events(){ //用於關閉視窗，重新開始遊戲 
		while(window->pollEvent(event)){ //事件發生時執行 
			if(event.type==Event::Closed){ //事件若為點擊關閉視窗 
				window->close(); //視窗物件關閉，即遊戲關閉 
			}
		}
	}
	void draw(){ //刷新畫面，渲染並顯示圖示 
		window->clear(); //清除整個畫面，用於刷新畫面，達到動畫效果 
		window->draw(*background); //待執行顯示背景 
		for(auto &p:pipes){ //遍歷所有管道 
			window->draw(p); //待執行顯示管道 
		}
		window->draw(*bird); //待執行顯示鳥 
		window->draw(text_score); //待執行顯示分數
		window->draw(ann_space); 
		window->display(); //呼叫OpenGL渲染完成後調用(對當前幀的所有待顯示圖像顯示在畫面上) 
	}
	void pipeMove(){ //用於移動水管，與鳥的跳躍 
		if(count%150==0){ //每執行150次時 
			int pos=rand()%315+25; //設定隨機高度 
			pipeTop->setPosition(1000,pos);  //上管道設定位置
			pipeBottom->setPosition(1000,pos+interval); //下管道設定位置 
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
				_gameOver();//呼叫遊戲結束之函數 
			}
			if(pipes[i].getPosition().x < -150 ){ //管道的x軸在畫面左側150(超出畫面) 
				pipes.erase(pipes.begin() + i );  //清除管道 
			} 
			pipes[i].move(-4.f, 0); //管道向左移動 
			if(pipes[i].getPosition().x==408&&!addscore){ //當管道比鳥更靠左側，且還未加分 
				text_score.setString(to_string(++score)); //顯示分數增加 
				sound_add.play(); //播放加分音效  
				addscore = true; //設定已經加過分數了，避免上下管道都加分 
			}else //另一個管道通過，將其設定還未加過分數，使下次能繼續加分 
				addscore = false;
		}}
	void birdAnime(){ //設定鳥的動畫 
		frame += 0.15f; // 設定幀 
		if(frame>3){ // 當大於三
			frame -= 3; // 設為-3，製造循環的感覺 
		}	
		bird->setTextureRect(IntRect(34 * (int)frame, 0, 34, 24)); //設定圖示取樣範圍 
	}	
	void birdMove(){ //移動鳥
		if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //高度25禁止往上
			any_timing =0;//從0數要轉白的時機 
			ann_space.setColor(Color::Red);//讓Space轉紅 
			sound_wing.play(); //播放揮翅膀音效 
			bird->setRotation(-frame*2 - 10.f); //旋轉稍微向上看 
			g=-8.f; //設定重量向下 
		}
		else
			bird->setRotation(frame*2 - 10.f); //旋轉稍微向下看
		if(any_timing>=10){
			ann_space.setColor(Color::White); //讓Space轉白 
		}else{
			any_timing++;//轉白前的倒數 
		}
		bird->move(0, g); //向下墜落 
		g+=0.5f; //逐漸增快 
		if(bird->getPosition().y>650){ //當整個鳥超出畫面(y>650) 
			_gameOver(); //呼叫遊戲失敗之函數 
		}
	}	
	void gameAnime(){ //執行精靈移動與鳥的跳躍和動畫 
		if(!gameover){ //還沒結束遊戲
			birdAnime(); //呼叫鳥的動畫 
			birdMove(); //呼叫鳥的位移 
			pipeMove(); //呼叫管道的位移 
		}
	}	
	void run(){ //執行遊戲主體之Function 
		while(!gameover){ //當視窗還開著
			events(); //呼叫函數events，用於關閉視窗，重新開始遊戲 
			gameAnime(); //呼叫函數game，執行精靈移動與鳥的跳躍和動畫 
			draw(); //呼叫函數draw，刷新畫面，渲染並顯示圖示
			count++; //常數增加，用於管道生成
			bgmCircle(); //bgm循環 
			if(count == 300) //常數等於300 
				count = 0; //常數重置
		}
	}
	void reset_Bird(){ //重新設定遊戲中鳥的精靈(圖像) 
		bird->setTexture(bd);  //精靈圖案設為鳥 
		bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //設定鳥的初始位置 
		bird->setScale(2.f, 2.f); //調整大小(比例)
		bird->setTextureRect(IntRect(0, 0, 34, 24)); //取用圖片中，最左側的鳥 
	}
	void home_BirdAnime(){ //首頁中鳥的動畫 
		frame+=0.15f; // 設定幀 
		if(frame>3) // 當大於三
			frame-=3; // 設為-3，製造循環的感覺 
		bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //設定圖示取樣範圍
		bird->move(0, g); //向下墜落 
		if(bird->getPosition().y>90) //鳥快撞到Play按鈕之前要停下來 
			g-=0.05f; //逐漸減速，最後上升 
		else if(bird->getPosition().y<50) //鳥快撞到視窗頂部之前要停下來 
			g+=0.05f; //逐漸減速，最後下降 
	}
	void bgmCircle(){ //bgm播放 
		if(bgm_timing>=1320){ //循環時機 
			bgm_timing = 0; //初始化bgm_timing 
			sound_bgm.play(); //重新播放bgm 
		}else{
			bgm_timing++; //記數+1 
		}
	}
	void changeWindow(){ //改變視窗之函數 
		sound_bgm.play(); //bgm音樂播放
		while( window->isOpen() ){ //當window開啟狀態 
			bgmCircle(); //呼叫背景音樂循環函數 
			window->clear(); //清空畫面，清除上一幀的內容 
			window->draw(*background); //預渲染背景 
			switch(gamestatus){ //遊戲狀態之判斷與執行不同動作 
				case _homepage: //當在首頁時 
					while(window->pollEvent(event)){ //偵測視窗事件 
						if (event.type == sf::Event::Closed) //視窗被按下關閉(x) 
			                		window->close(); //關閉視窗
			            		if(button_play->button_Mouse(*window)){//若play按鈕被按下 
							button_Play(); //執行Play動作 
						}
						if(button_rank->button_Mouse(*window)){//若rank按鈕被按下
							button_Rank(); //執行Rank動作
						}
						if(button_intro->button_Mouse(*window)){//若intro按鈕被按下
							button_Introduce(); //執行Introduce動作
						}
					}
					home_BirdAnime(); //呼叫首頁鳥的動畫 
					window->draw(*button_play->sbtn); //預渲染play按鈕 
					window->draw(*button_rank->sbtn); //預渲染rank按鈕 
					window->draw(*button_intro->sbtn); //預渲染introduce按鈕 
					window->draw(*bird); //預渲染bird按鈕 
					window->display(); //執行渲染 
					break;
				case _inputname:
					while(window->pollEvent(event)){ //偵測視窗事件 
						if(event.type == Event::Closed) //視窗被按下關閉(x)
			               			 window->close(); //關閉視窗
						if(button_home->button_Mouse(*window)){ //若home按鈕被按下
							button_Homepage(); //執行Homepage動作
						} 
						if(button_enter->button_Mouse(*window)){ //若enter按鈕被按下
							button_Enter(); //執行Enter動作
						} 
					}
					window->draw(*button_home->sbtn); //預渲染home按鈕
					window->draw(*button_enter->sbtn); //預渲染enter按鈕 
					window->draw(text_announce); //預渲染text announce 
					textbox1->drawTo(*window); //預渲染textbox1 
					window->display(); //執行渲染 
					break;
				case _game:
					score = 0; //初始化分數
					bgm_timing=0; //初始化背景音樂循環時機 
					g =  frame = 0.f; //初始化重量、幀(用於設定鳥的圖示與傾角)
					text_score.setString(to_string(score)); //初始化分數文字內容 
					pipes.clear(); //管道全部清除
					bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //初始化鳥的座標 
					gameover = false; //設結束結束為否 
					reset_Bird();//重設鳥的圖片 
					run(); //執行遊戲 
					break; 
				case _gameover:
					while(window->pollEvent(event)){ //偵測視窗事件  
						if(event.type == sf::Event::Closed) //視窗被按下關閉(x)
			                		window->close(); //關閉視窗
			            		if(button_restart->button_Mouse(*window)){ //若restart按鈕被按下
							button_Restart(); //執行Restart動作
						}
						if(button_home->button_Mouse(*window)){ //若home按鈕被按下
							button_Homepage(); //執行Homepage動作
						} 
					}	
					for(auto &p:pipes){ //遍歷所有管道 
						window->draw(p); //待執行顯示管道 
					}
					window->draw(*bird); //預渲染鳥
					window->draw(text_score); //預渲染分數 
					window->draw(*button_restart->sbtn);  //預渲染restart按鈕
					window->draw(*button_home->sbtn); //預渲染home按鈕
					window->draw(text_rank); //預渲染目前排行與歷史最高 
					window->display(); //執行渲染 
					break;
				case _showrank:
					_showRank();//顯示排行之函數 
					while(window->pollEvent(event)){ //偵測視窗事件  
						if(event.type == sf::Event::Closed) //視窗被按下關閉(x) 
			                window->close(); //關閉視窗
						if(Keyboard::isKeyPressed(Keyboard::Up)){//修改上箭頭顏色-紅 
							any_timing=0;//設定箭頭轉紅時間 
							arrow_up.setColor(Color::Red);//上箭頭改成紅 
								if(rankfield>0)//顯示排名最高是第一名 
									rankfield--;//顯示排名往上 
						}
						if(Keyboard::isKeyPressed(Keyboard::Down)){//修改下箭頭顏色-紅 
							any_timing=0;//設定箭頭轉紅時間
							arrow_down.setColor(Color::Red);//下箭頭改成紅 
							if(rankfield<v.size()-1)//顯示排名最低最後一名
								rankfield++;//顯示排名往下
							}
						if(button_home->button_Mouse(*window)){ //若home按鈕被按下
							button_Homepage(); //執行Homepage動作
						}
					}
					
					if(any_timing>=10){//當經過10次switch箭頭改成白 
						arrow_up.setColor(Color::White); //修改上箭頭顏色-白 
						arrow_down.setColor(Color::White);//修改下箭頭顏色-白 
					}else
						any_timing++;//箭頭轉紅計數+1
					window->draw(arrow_up);//預渲染向上箭頭 
					window->draw(arrow_down);//預渲染向下箭頭 
					window->draw(text_rank); //預渲染排行榜 
					window->draw(*button_home->sbtn); //預渲染home按鈕 
					window->display(); //執行渲染 
					break;
				case _introduce:
					while(window->pollEvent(event)){ //偵測視窗事件
						if(event.type == sf::Event::Closed) //視窗被按下關閉(x) 
			                		window->close();//關閉視窗
						if(button_home->button_Mouse(*window)) //若home按鈕被按下
							button_Homepage(); //執行Homepage動作
					}
					window->draw(*team_picture); //預渲染小組照片 
					window->draw(*button_home->sbtn); //預渲染home按鈕 
					window->draw(text_introduce);  //預渲染介紹 text 
					window->display(); //執行渲染
					break;
				dafault: //default 理論上遊戲狀態沒有例外 
					gamestatus = _homepage; //如果發生例外，跳至首頁 
					break;
			}
		}
	}
	
	void button_Play(){ //Play按鈕按下之動作函數
		gamestatus = _inputname; //進入輸入名稱 
	}
	void button_Rank(){ //Rank按鈕按下之動作函數 
		gamestatus = _showrank; //進入排行榜 
	}
	void button_Introduce(){ //Introduce按鈕按下之動作函數
		gamestatus = _introduce; //進入介紹 
	}
	
	void button_Enter(){ //Enter按鈕按下之動作函數
		name=textbox1->getText();//name設定為textbox1之內容	
		sound_bgm.play(); //bgm播放 
		gamestatus = _game; //進入遊戲 
	}
	void button_Restart(){ //Restart按鈕按下之動作函數
		sound_bgm.play(); //bgm播放
		gamestatus = _game; //進入遊戲 
	}
	void button_Homepage(){ //Homepage按鈕按下之動作函數 
		sound_bgm.play(); //bgm播放
		bgm_timing=0; //重製bgm迴圈時機 
		gamestatus = _homepage; //進入首頁 
		g =  frame = 0.f; //預設首頁鳥向下、幀(用於設定鳥的圖示與傾角) 
		setPictureSize(bird,&bd,2.5f,3,500,75); //設定鳥的圖片、大小與位置 
		bird->setRotation(0); //設定鳥的轉角 
	}
	public:
	FlappyBird(){ //建構元(子)，設定初始值 
	  setSFML(); //由於SFML套件的物件設定不可在建構子執行，所以另外呼叫函數 
	}
};
