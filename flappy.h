#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "set_rank.h"
#include "testbox.hpp"
#define TEAMNAME "111_2 NO.5 TEAM - Flappy bird"
#define SOUND_HIT "./AllSundries/sound/hit.wav"
#define SOUND_ADD "./AllSundries/sound/add.wav"
#define SOUND_BGM "./AllSundries/sound/bgm.wav"
#define SOUND_WING "./AllSundries/sound/wing.wav"
#define SOUND_NO1 "./AllSundries/sound/no1.wav"
#define BACKGROUND "./AllSundries/image/background.png"
#define BIRD "./AllSundries/image/bird.png"
#define PIPE "./AllSundries/image/pipe.png"
#define FONT "./AllSundries/font/flappybird.ttf"
#define BUTTON_START "./AllSundries/button/play.png"
#define BUTTON_ENTER "./AllSundries/button/enter.png"
#define BUTTON_RESTART "./AllSundries/button/restart.png"
#define BUTTON_HOMEPAGE "./AllSundries/button/home.png"
#define BUTTON_SHOWRANK "./AllSundries/button/rank.png"
#define BUTTON_INTRODUCE "./AllSundries/button/intro.png"
using namespace std;
using namespace sf;
enum Status{_homepage, _inputname, _game, _gameover, _showrank, _introduce};
class FlappyBird : protected setrank{
	private:
	Event event;
	Texture btn_start,btn_enter,btn_restart,btn_homepage,btn_showrank,btn_introduce;
	Sprite *sbtn_start,*sbtn_enter,*sbtn_restart,*sbtn_homepage,*sbtn_showrank,*sbtn_introduce;
	float mouse_x,mouse_y,btn_x,btn_y,btn_w,btn_h;	
	RenderWindow *window;
	float y,g,frame,interval;
	int count,bgm_times,now_rank;
	string name,show_name,showrank;
	long long score,history_high;
	pair<int,long long> now;
	SoundBuffer buffer_hit,buffer_wing,buffer_add,buffer_bgm,buffer_no1;
	Sound sound_hit,sound_wing,sound_add,sound_bgm,sound_no1;
	Font font;
	Text text_score,text_rank,text_introduce,text_announce;
	Texture bg, bd, pipe,btn;
	Sprite *background, *bird, *pipeBottom, *pipeTop;
	vector<Sprite> pipes;
	bool gameover, addscore;
	Status gamestatus = _homepage;
	Textbox *textbox1;
	void _showRank(){
		showrank="";
		if(v.size()==0)
			showrank="No Data";
		for(int i=0;i<v.size();i++){
			showrank+="NO."+to_string(i+1)+" "+v[i].first+" Score:"+to_string(v[i].second)+"\n";
			if(i==4)
				break;
		}
		text_rank.setString(showrank);
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,300-text_rank.getGlobalBounds().height/2.f);
	}
	void _gameOver(){
		sound_hit.play(); //播放撞擊音效
		gameover = true; //遊戲結束 
		gamestatus=_gameover;
		now = renewrank({name,score});
		now_rank=now.first;
		history_high=now.second;
		text_rank.setString("NO."+to_string(now_rank)+" "+show_name+" Score:"+to_string(score)+" History:"+to_string(history_high));
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,187.5f);
		if(now_rank==1&&score>=history_high){
			sound_bgm.stop();
			bgm_times=1000;
			sound_no1.play();
		}		
	}
	void setSFML(){ //用於設定初始值
		
		name="";
		show_name="";
		//參數設定 
		g = 2.0f;
		frame = 0.f; //設定初始重量、幀(用於設定鳥的圖示與傾角) 
		interval = 240.f; //設定管道區間 
		count = 0; //常數-用於生成管道
		bgm_times = 0; //設定背景音樂播放之正記數 
		gameover = addscore = false;  //結束、加分為否 
		score = 0;  //分數為0 
		//視窗設定 
		window = new RenderWindow(VideoMode(1000, 600),TEAMNAME); //視窗設定 
		window->setPosition(Vector2i(0, 0)); //初始化視窗座標左上角(0,0) 
		window->setKeyRepeatEnabled(true);
		//調控遊戲速度 
		window->setFramerateLimit( 60 ); //限制最大幀數，由於它在內部使用 sf::sleep，其精度取決於底層操作系統，結果也可能有點不精確，
		//window->setFramerateLimit( 0 ); //無幀數限制，遊戲以最快的速度進行 
		textbox1 = new Textbox(40,Color::White,true);
		/*以下是背景的圖與精靈設定*/
		if(!bg.loadFromFile(BACKGROUND))//載入圖片
			cout<<"Fail loading background.png"<<endl;   
		background = new Sprite(); //建立精靈
		background -> setTexture(bg); //精靈圖案設為背景圖
		//無須設定位置與大小 初始位置為(0,0) 視窗與圖等大 
		
		/*以下是鳥的圖與精靈設定*/
		if(!bd.loadFromFile(BIRD))//載入圖片
			cout<<"Fail loading bird.png"<<endl;  
		bird = new Sprite(); //建立精靈 
		setPictureSize(bird,&bd,2.5f,3,500,75);
		
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
		
		/*以下是分數的字體與文字設定*/
		text_score.setFont(font); //套用字型 
		text_score.setString(to_string(score)); //文字內容設定  
		text_score.setPosition(10.f, 10.f); //位置設定
		text_score.setCharacterSize(50); //字體大小設定
		text_score.setOutlineThickness(3); //字體粗細設定
		
		/*以下是分數的字體與文字設定*/
		text_score.setFont(font); //套用字型 
		text_score.setString(to_string(score)); //文字內容設定  
		text_score.setPosition(10.f, 10.f); //位置設定
		text_score.setCharacterSize(50); //字體大小設定
		text_score.setOutlineThickness(3); //字體粗細設定
		
		/*以下是排名的字體與文字設定*/
		text_rank.setFont(font); //套用字型 
		//text_rank.setString("NO."+to_string(1)+"  "+show_name+"   "+to_string(100)); //文字內容設定  
		text_rank.setPosition(10.f, 250.f); //位置設定
		text_rank.setCharacterSize(50); //字體大小設定
		text_rank.setOutlineThickness(3); //字體粗細設定
		
		/*以下是介紹的字體與文字設定*/
		text_introduce.setFont(font);
		text_introduce.setPosition(10.f, 100.f);
		text_introduce.setCharacterSize(30); //字體大小設定
		text_introduce.setOutlineThickness(3); //字體粗細設定
		text_introduce.setString("This Flappy Bird game is created by B1143007 Lee Min-Chen, B114\n3009 Wu Bing-Rong, B1143015 Lin Xuan-You, B1143021 Lin Cheng-Wei\n, B1143027 ChenBo-Hao, and B1143036 Huang Qi-Ting, is a simple \nbut addictive game. Guide the bird through pipes by tapping the \nscreen or pressing spacebar. Avoid collisions with pipes and \nthe ground. Score points for each successful passage. \nChallenge yourself with increasing difficulty. Aim for the \nhighest score and compete with friends.");
		
		/*以下是輸入文字提示的字體與文字設定*/ 
		text_announce.setFont(font); //套用字型 
		text_announce.setString("Name : \nWarning  :Don't using space in the \nfirst char"); //文字內容設定  
		text_announce.setPosition(100.f, 100.f); //位置設定
		text_announce.setCharacterSize(40); //字體大小設定
		text_announce.setOutlineThickness(3); //字體粗細設定
		
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
		
		sbtn_start=new Sprite();
		sbtn_showrank=new Sprite();
		sbtn_introduce=new Sprite();
		sbtn_restart=new Sprite();
		sbtn_enter=new Sprite();
		sbtn_homepage=new Sprite();
		
		btn_start.loadFromFile(BUTTON_START);
		btn_showrank.loadFromFile(BUTTON_SHOWRANK);
		btn_introduce.loadFromFile(BUTTON_INTRODUCE);
		btn_restart.loadFromFile(BUTTON_RESTART);
		btn_enter.loadFromFile(BUTTON_ENTER);
		btn_homepage.loadFromFile(BUTTON_HOMEPAGE);
		
		setPictureSize(sbtn_start,&btn_start,0.4f,2,500.f,250.f);
		setPictureSize(sbtn_showrank,&btn_showrank,0.4f,2,500.f,375.f);
		setPictureSize(sbtn_introduce,&btn_introduce,0.4f,2,500.f,500.f);
		setPictureSize(sbtn_restart,&btn_restart,0.4f,2,500.f,375.f);
		setPictureSize(sbtn_enter,&btn_enter,0.4f,2,500.f,500.f);
		setPictureSize(sbtn_homepage,&btn_homepage,0.4f,2,500.f,500.f);
		
		textbox1->setFont(font);
		textbox1->setPosition({240,100});  //textbox位置 
		textbox1->setLimit(true,20);  //設定是否設限and字數限制
	}
	void setPictureSize(Sprite *spt,Texture *txt,float resize,float cut,float px,float py){
		spt->setTexture(*txt);
		spt->setScale(resize,resize);
		spt->setTextureRect(IntRect(0,0,txt->getSize().x/cut,txt->getSize().y));
		spt->setPosition(px-spt->getGlobalBounds().width/2.f,py-spt->getGlobalBounds().height/2.f);
	}
	void events(){ //用於關閉視窗，重新開始遊戲 
		auto e = new Event(); //視窗事件物件設定 
		while( window->pollEvent( *e ) ){ //事件發生時執行 
			if( e->type == Event::Closed){ //事件若為點擊關閉視窗 
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
		window->display(); //呼叫OpenGL渲染完成後調用(對當前幀的所有待顯示圖像顯示在畫面上) 
	}
	void pipeMove(){ //用於移動水管，與鳥的跳躍 
		if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //高度25禁止往上
			sound_wing.play(); //播放揮翅膀音效 
			bird->setRotation(-frame*2 - 10.f); //旋轉稍微向上看 
			g = -8.f; //設定重量向下 
		}
		else
			bird->setRotation(frame*2 - 10.f); //旋轉稍微向下看
		if( count % 150 == 0 ){ //每執行150次時 
			int pos = rand() % 315 + 25; //設定隨機高度 
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
				_gameOver();
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
		}}
	void birdAnime(){ //設定鳥的動畫 
		frame += 0.15f; // 設定幀 
		if( frame > 3 ){ // 當大於三
			frame -= 3; // 設為-3，製造循環的感覺 
		}	
		bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //設定圖示取樣範圍 
	}	
	void birdMove(){ //移動鳥 
		bird->move(0, g); //向下墜落 
		g += 0.5f; //逐漸增快 
		if(bird->getPosition().y>650){ //當整個鳥超出畫面(y>650) 
			_gameOver();
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
			bgmCircle();
			if( count == 300 ){ //常數等於300 
				count = 0; //常數重製
				 //呼叫音樂重複播放 
			}
		}
	}
	void reset_Bird(){ //重新設定遊戲中鳥的精靈(圖像) 
		bird->setTexture(bd);  //精靈圖案設為鳥 
		bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //設定鳥的初始位置 
		bird->setScale(2.f, 2.f); //調整大小(比例)
		bird->setTextureRect(IntRect(0, 0, 34, 24)); //取用圖片中，最左側的鳥 
	}
	void home_BirdAnime(){ //首頁中鳥的動畫 
		frame += 0.15f; // 設定幀 
		if( frame > 3 ) // 當大於三
			frame -= 3; // 設為-3，製造循環的感覺 
		bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //設定圖示取樣範圍
		bird->move(0, g); //向下墜落 
		if(bird->getPosition().y>90)
			g-=0.05f;
		else if(bird->getPosition().y<50)
			g+=0.05f;
	}
	void bgmCircle(){ //音樂重複播放 
		if(bgm_times>=1320){
			bgm_times=0; //初始化bgm_times 
			sound_bgm.play(); //重新播放bgm 
		}else{
			bgm_times++; //記數+1 
		}
	}
	bool isMouseOver(Sprite *sbtn){
		mouse_x = Mouse::getPosition(*window).x;
		mouse_y = Mouse::getPosition(*window).y;
		btn_x = sbtn->getPosition().x;
		btn_y = sbtn->getPosition().y;
		btn_w = sbtn->getPosition().x + sbtn->getGlobalBounds().width;
		btn_h = sbtn->getPosition().y + sbtn->getGlobalBounds().height;
		
		if (mouse_x < btn_w && mouse_x > btn_x && mouse_y < btn_h && mouse_y > btn_y)
			return true;
		return false;	
	}
	void changeWindow(){
		sound_bgm.play(); //bgm音樂播放
		while( window->isOpen() ){
			bgmCircle();
			window->clear();
			window->draw(*background);
			switch(gamestatus){
				case _homepage:
					while(window->pollEvent(event)){
						if (event.type == sf::Event::Closed)
			                window->close();
						button_Start();
						button_Rank();
						button_Introduce();
					}
					home_BirdAnime();
					window->draw(*sbtn_start);
					window->draw(*sbtn_showrank);
					window->draw(*sbtn_introduce);
					window->draw(*bird);
					window->display();
					break;
				case _inputname:
					while(window->pollEvent(event)){
						if(event.type == Event::Closed)
			                window->close();
			            if(event.type == Event::TextEntered){  //文字輸入判定 
			            	textbox1->typedOn(event);
						}
						button_Enter();
					}
					window->draw(*sbtn_enter);
					window->draw(text_announce);
					textbox1->drawTo(*window);
					window->display();
					break;
				case _game:
					score = 0; //初始化分數
					bgm_times=0;
					g =  frame = 0.f; //初始化重量、幀(用於設定鳥的圖示與傾角)
					text_score.setString(to_string(score)); //初始化分數文字內容 
					pipes.clear(); //管道全部清除
					bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //初始化鳥的座標 
					gameover = false; //設結束結束為否 
					reset_Bird();
					run();
					break;
				case _gameover:
					while(window->pollEvent(event)){
						if(event.type == sf::Event::Closed)
			                window->close();
						button_Restart();
						button_Homepage();
					}	
					for(auto &p:pipes){ //遍歷所有管道 
						window->draw(p); //待執行顯示管道 
					}
					window->draw(*bird); //待執行顯示鳥
					window->draw(text_score); //待執行顯示分數 
					window->draw(*sbtn_homepage);
					window->draw(*sbtn_restart);
					window->draw(text_rank);
					window->display();
					break;
				case _showrank:
					_showRank();
					while(window->pollEvent(event)){
						if(event.type == sf::Event::Closed)
			                window->close();
						button_Homepage();
					}
					window->draw(text_rank);
					window->draw(*sbtn_homepage);
					window->display();
					break;
				case _introduce:
					while(window->pollEvent(event)){
						if(event.type == sf::Event::Closed)
			                window->close();
						button_Homepage();
					}
					window->draw(*sbtn_homepage);
					window->draw(text_introduce);
					window->display();
					break;
				dafault:
					break;
			}
		}
	}
	void button_Start(){
		if (isMouseOver(sbtn_start)){
			sbtn_start->setTextureRect(IntRect(btn_start.getSize().x/2.f,0,btn_start.getSize().x/2.f,btn_start.getSize().y)); //改成滑鼠在上圖片 
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _inputname;
			}
		}else{
			sbtn_start->setTextureRect(IntRect(0,0,btn_start.getSize().x/2.f,btn_start.getSize().y));
		}
	}
	void button_Rank(){
		if (isMouseOver(sbtn_introduce)){
			sbtn_introduce->setTextureRect(IntRect(btn_introduce.getSize().x/2.f,0,btn_introduce.getSize().x/2.f,btn_introduce.getSize().y)); //改成滑鼠在上圖片
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _introduce;
			}
		}else{
			sbtn_introduce->setTextureRect(IntRect(0,0,btn_introduce.getSize().x/2.f,btn_introduce.getSize().y));
		}
	}
	void button_Introduce(){
		if (isMouseOver(sbtn_showrank)){
			sbtn_showrank->setTextureRect(IntRect(btn_showrank.getSize().x/2.f,0,btn_showrank.getSize().x/2.f,btn_showrank.getSize().y)); //改成滑鼠在上圖片 
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _showrank;
			}
		}else{
			sbtn_showrank->setTextureRect(IntRect(0,0,btn_showrank.getSize().x/2.f,btn_showrank.getSize().y));
		}
	}
	void button_Enter(){
		show_name="";
		if(isMouseOver(sbtn_enter)){
			sbtn_enter->setTextureRect(IntRect(btn_enter.getSize().x/2.f,0,btn_enter.getSize().x/2.f,btn_enter.getSize().y)); //改成滑鼠在上圖片 
			if (Mouse::isButtonPressed(Mouse::Left)){
				name=textbox1->getText();
				if( name[0] ==' '||name[0] =='\0'){
					cout<<"name format error"<<endl;//show warning about name format error
				}
				else{
					for(char &c:name){
						show_name+=c;
					}
					gamestatus = _game;
					sound_bgm.play();
				}
			}
		}else{
			sbtn_enter->setTextureRect(IntRect(0,0,btn_enter.getSize().x/2.f,btn_enter.getSize().y));
		}
	}
	void button_Restart(){
		if(isMouseOver(sbtn_restart)){
			sbtn_restart->setTextureRect(IntRect(btn_restart.getSize().x/2.f,0,btn_restart.getSize().x/2.f,btn_restart.getSize().y)); //改成滑鼠在上圖片
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _game;
			}
		}else{
			sbtn_restart->setTextureRect(IntRect(0,0,btn_restart.getSize().x/2.f,btn_restart.getSize().y));
		}	
	}
	void button_Homepage(){
		if(isMouseOver(sbtn_homepage)){
			sbtn_homepage->setTextureRect(IntRect(btn_homepage.getSize().x/2.f,0,btn_homepage.getSize().x/2.f,btn_homepage.getSize().y)); //改成滑鼠在上圖片 
			if (Mouse::isButtonPressed(Mouse::Left)){
				sound_bgm.play();
				bgm_times=0;
				gamestatus = _homepage;
				g =  frame = 0.f;
				setPictureSize(bird,&bd,2.5f,3,500,75);
				bird->setRotation(0);
			}
		}else{
			sbtn_homepage->setTextureRect(IntRect(0,0,btn_homepage.getSize().x/2.f,btn_homepage.getSize().y));
		}
	}
	
	public:
	FlappyBird(){ //建構元(子)，設定初始值 
	  setSFML(); //由於SFML套件的物件設定不可在建構子執行，所以另外呼叫函數 
	}
	void flappy_start(){
		changeWindow();
	}
};
