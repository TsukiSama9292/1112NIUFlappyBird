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
		sound_hit.play(); //����������
		gameover = true; //�C������ 
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
	void setSFML(){ //�Ω�]�w��l��
		
		name="";
		show_name="";
		//�ѼƳ]�w 
		g = 2.0f;
		frame = 0.f; //�]�w��l���q�B�V(�Ω�]�w�����ϥܻP�ɨ�) 
		interval = 240.f; //�]�w�޹D�϶� 
		count = 0; //�`��-�Ω�ͦ��޹D
		bgm_times = 0; //�]�w�I�����ּ��񤧥��O�� 
		gameover = addscore = false;  //�����B�[�����_ 
		score = 0;  //���Ƭ�0 
		//�����]�w 
		window = new RenderWindow(VideoMode(1000, 600),TEAMNAME); //�����]�w 
		window->setPosition(Vector2i(0, 0)); //��l�Ƶ����y�Х��W��(0,0) 
		window->setKeyRepeatEnabled(true);
		//�ձ��C���t�� 
		window->setFramerateLimit( 60 ); //����̤j�V�ơA�ѩ󥦦b�����ϥ� sf::sleep�A���ר��M�󩳼h�ާ@�t�ΡA���G�]�i�঳�I����T�A
		//window->setFramerateLimit( 0 ); //�L�V�ƭ���A�C���H�̧֪��t�׶i�� 
		textbox1 = new Textbox(40,Color::White,true);
		/*�H�U�O�I�����ϻP���F�]�w*/
		if(!bg.loadFromFile(BACKGROUND))//���J�Ϥ�
			cout<<"Fail loading background.png"<<endl;   
		background = new Sprite(); //�إߺ��F
		background -> setTexture(bg); //���F�Ϯ׳]���I����
		//�L���]�w��m�P�j�p ��l��m��(0,0) �����P�ϵ��j 
		
		/*�H�U�O�����ϻP���F�]�w*/
		if(!bd.loadFromFile(BIRD))//���J�Ϥ�
			cout<<"Fail loading bird.png"<<endl;  
		bird = new Sprite(); //�إߺ��F 
		setPictureSize(bird,&bd,2.5f,3,500,75);
		
		/*�H�U�O�޹D���ϻP���F�]�w*/
		if(!pipe.loadFromFile(PIPE))//���J�Ϥ� 
			cout<<"Fail loading pipe.png"<<endl;
		pipe.loadFromFile(PIPE); //���J�Ϥ�
		pipeBottom = new Sprite(); //�إߺ��F 
		pipeTop = new Sprite(); //�إߺ��F 
		pipeBottom->setTexture(pipe); //���F�Ϯ׳]���޹D 
		pipeTop->setTexture(pipe); //���F�Ϯ׳]���޹D 
		pipeBottom->setScale(1.5f, 1.5f); //�վ�j�p(���)
		pipeTop->setScale(1.5f, -1.5f); //�վ�j�p(���)�A�t�Ƭ��A�� 
		
		/*�H�U�O�C���������r��P��r�]�w*/
		if(!font.loadFromFile(FONT))//���J�r�� 
			cout<<"Fail loading flappybird.ttf"<<endl; 
		
		/*�H�U�O���ƪ��r��P��r�]�w*/
		text_score.setFont(font); //�M�Φr�� 
		text_score.setString(to_string(score)); //��r���e�]�w  
		text_score.setPosition(10.f, 10.f); //��m�]�w
		text_score.setCharacterSize(50); //�r��j�p�]�w
		text_score.setOutlineThickness(3); //�r��ʲӳ]�w
		
		/*�H�U�O���ƪ��r��P��r�]�w*/
		text_score.setFont(font); //�M�Φr�� 
		text_score.setString(to_string(score)); //��r���e�]�w  
		text_score.setPosition(10.f, 10.f); //��m�]�w
		text_score.setCharacterSize(50); //�r��j�p�]�w
		text_score.setOutlineThickness(3); //�r��ʲӳ]�w
		
		/*�H�U�O�ƦW���r��P��r�]�w*/
		text_rank.setFont(font); //�M�Φr�� 
		//text_rank.setString("NO."+to_string(1)+"  "+show_name+"   "+to_string(100)); //��r���e�]�w  
		text_rank.setPosition(10.f, 250.f); //��m�]�w
		text_rank.setCharacterSize(50); //�r��j�p�]�w
		text_rank.setOutlineThickness(3); //�r��ʲӳ]�w
		
		/*�H�U�O���Ъ��r��P��r�]�w*/
		text_introduce.setFont(font);
		text_introduce.setPosition(10.f, 100.f);
		text_introduce.setCharacterSize(30); //�r��j�p�]�w
		text_introduce.setOutlineThickness(3); //�r��ʲӳ]�w
		text_introduce.setString("This Flappy Bird game is created by B1143007 Lee Min-Chen, B114\n3009 Wu Bing-Rong, B1143015 Lin Xuan-You, B1143021 Lin Cheng-Wei\n, B1143027 ChenBo-Hao, and B1143036 Huang Qi-Ting, is a simple \nbut addictive game. Guide the bird through pipes by tapping the \nscreen or pressing spacebar. Avoid collisions with pipes and \nthe ground. Score points for each successful passage. \nChallenge yourself with increasing difficulty. Aim for the \nhighest score and compete with friends.");
		
		/*�H�U�O��J��r���ܪ��r��P��r�]�w*/ 
		text_announce.setFont(font); //�M�Φr�� 
		text_announce.setString("Name : \nWarning  :Don't using space in the \nfirst char"); //��r���e�]�w  
		text_announce.setPosition(100.f, 100.f); //��m�]�w
		text_announce.setCharacterSize(40); //�r��j�p�]�w
		text_announce.setOutlineThickness(3); //�r��ʲӳ]�w
		
		/*�H�U�O���ĳ]�w*/
		if(!buffer_hit.loadFromFile(SOUND_HIT)) //���J����_hit 
			cout<<"Fail loading hit.wav"<<endl; //���J����_hit 
		if(!buffer_wing.loadFromFile(SOUND_WING)) //���J����_wing
			cout<<"Fail loading wing.wav"<<endl; //���J����_wing 
		if(!buffer_add.loadFromFile(SOUND_ADD)) //���J����_add
			cout<<"Fail loading add.wav"<<endl;	//���J����_add
		if(!buffer_bgm.loadFromFile(SOUND_BGM)) //���J����_bgm
			cout<<"Fail loading bgm.wav"<<endl; //���J����_bgm
		if(!buffer_no1.loadFromFile(SOUND_NO1)) //���J����_no1
			cout<<"Fail loading no1.wav"<<endl; //���J����_no1
		sound_hit.setBuffer(buffer_hit); //���ļ��񾹳]�w_hit 
		sound_wing.setBuffer(buffer_wing); //���ļ��񾹳]�w_wing
		sound_add.setBuffer(buffer_add); //���ļ��񾹳]�w_add
		sound_bgm.setBuffer(buffer_bgm); //���ļ��񾹳]�w_bgm 
		sound_no1.setBuffer(buffer_no1); //���ļ��񾹳]�w_no1
		
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
		textbox1->setPosition({240,100});  //textbox��m 
		textbox1->setLimit(true,20);  //�]�w�O�_�]��and�r�ƭ���
	}
	void setPictureSize(Sprite *spt,Texture *txt,float resize,float cut,float px,float py){
		spt->setTexture(*txt);
		spt->setScale(resize,resize);
		spt->setTextureRect(IntRect(0,0,txt->getSize().x/cut,txt->getSize().y));
		spt->setPosition(px-spt->getGlobalBounds().width/2.f,py-spt->getGlobalBounds().height/2.f);
	}
	void events(){ //�Ω����������A���s�}�l�C�� 
		auto e = new Event(); //�����ƥ󪫥�]�w 
		while( window->pollEvent( *e ) ){ //�ƥ�o�ͮɰ��� 
			if( e->type == Event::Closed){ //�ƥ�Y���I���������� 
				window->close(); //�������������A�Y�C������ 
			}
		}
	}
	void draw(){ //��s�e���A��V����ܹϥ� 
		window->clear(); //�M����ӵe���A�Ω��s�e���A�F��ʵe�ĪG 
		window->draw(*background); //�ݰ�����ܭI�� 
		for(auto &p:pipes){ //�M���Ҧ��޹D 
			window->draw(p); //�ݰ�����ܺ޹D 
		}
		window->draw(*bird); //�ݰ�����ܳ� 
		window->draw(text_score); //�ݰ�����ܤ��� 
		window->display(); //�I�sOpenGL��V������ե�(���e�V���Ҧ�����ܹϹ���ܦb�e���W) 
	}
	void pipeMove(){ //�Ω󲾰ʤ��ޡA�P�������D 
		if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //����25�T��W
			sound_wing.play(); //���񴧯ͻH���� 
			bird->setRotation(-frame*2 - 10.f); //����y�L�V�W�� 
			g = -8.f; //�]�w���q�V�U 
		}
		else
			bird->setRotation(frame*2 - 10.f); //����y�L�V�U��
		if( count % 150 == 0 ){ //�C����150���� 
			int pos = rand() % 315 + 25; //�]�w�H������ 
			pipeTop->setPosition(1000, pos);  //�W�޹D�]�w��m
			pipeBottom->setPosition(1000, pos + interval); //�U�޹D�]�w��m 
			pipes.push_back(*pipeTop); //�޹Dvector�s�W�W�޹D 
			pipes.push_back(*pipeBottom); //�޹Dvector�s�W�U�޹D  
		}
		for (size_t i {}; i < pipes.size(); i++) { //�Q��size_t �M������  
			if(pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds())){ //�ͦ��޹D�B�P�����x�ΡA�p�G��x�Υ��|�A���� 
				/*/�]���ͦ��x�η|���޹D�B���Ϥ��H�����઺�A���Y��L���x�Τj�p(�z���]��)�i��ͦ��A�ɭP�ǳ\�j�p���t 
				���F�����ݰ_�ӹ��O���W�h�A�ҥH���������V�e����*/
				bird->move(15.f, 0); 
				if( pipes[i].getScale().y < 0 ) //�p�G(�I���޹Dy�b����Ҥp��0�A�Y�O�W�޹D)�A���� 
					bird->move(0,-10.f); //�y�L�V�W 
				else //�Y���U�޹D 
					bird->move(0,10.f); //�y�L�V�U 
				_gameOver();
			}
			if(pipes[i].getPosition().x < -150 ){ //�޹D��x�b�b�e������150(�W�X�e��) 
				pipes.erase(pipes.begin() + i );  //�M���޹D 
			} 
			pipes[i].move(-4.f, 0); //�޹D�V������ 
			if(pipes[i].getPosition().x == 408 && !addscore ){ //��޹D�񳾧�a�����A�B�٥��[�� 
				text_score.setString(to_string(++score)); //��ܤ��ƼW�[ 
				sound_add.play(); //����[������  
				addscore = true; //�]�w�w�g�[�L���ƤF�A�קK�W�U�޹D���[�� 
			}else //�t�@�Ӻ޹D�q�L�A�N��]�w�٥��[�L���ơA�ϤU�����~��[�� 
				addscore = false;
		}}
	void birdAnime(){ //�]�w�����ʵe 
		frame += 0.15f; // �]�w�V 
		if( frame > 3 ){ // ��j��T
			frame -= 3; // �]��-3�A�s�y�`�����Pı 
		}	
		bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //�]�w�ϥܨ��˽d�� 
	}	
	void birdMove(){ //���ʳ� 
		bird->move(0, g); //�V�U�Y�� 
		g += 0.5f; //�v���W�� 
		if(bird->getPosition().y>650){ //���ӳ��W�X�e��(y>650) 
			_gameOver();
		}
	}	
	void gameAnime(){ //������F���ʻP�������D�M�ʵe 
		if(!gameover){ //�٨S�����C��
			birdAnime(); //�I�s�����ʵe 
			birdMove(); //�I�s�����첾 
			pipeMove(); //�I�s�޹D���첾 
		}
	}	
	void run(){ //����C���D�餧Function 
		while(!gameover){ //������ٶ}��
			events(); //�I�s���events�A�Ω����������A���s�}�l�C�� 
			gameAnime(); //�I�s���game�A������F���ʻP�������D�M�ʵe 
			draw(); //�I�s���draw�A��s�e���A��V����ܹϥ�
			count++; //�`�ƼW�[�A�Ω�޹D�ͦ�
			bgmCircle();
			if( count == 300 ){ //�`�Ƶ���300 
				count = 0; //�`�ƭ��s
				 //�I�s���֭��Ƽ��� 
			}
		}
	}
	void reset_Bird(){ //���s�]�w�C�����������F(�Ϲ�) 
		bird->setTexture(bd);  //���F�Ϯ׳]���� 
		bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //�]�w������l��m 
		bird->setScale(2.f, 2.f); //�վ�j�p(���)
		bird->setTextureRect(IntRect(0, 0, 34, 24)); //���ιϤ����A�̥������� 
	}
	void home_BirdAnime(){ //�����������ʵe 
		frame += 0.15f; // �]�w�V 
		if( frame > 3 ) // ��j��T
			frame -= 3; // �]��-3�A�s�y�`�����Pı 
		bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //�]�w�ϥܨ��˽d��
		bird->move(0, g); //�V�U�Y�� 
		if(bird->getPosition().y>90)
			g-=0.05f;
		else if(bird->getPosition().y<50)
			g+=0.05f;
	}
	void bgmCircle(){ //���֭��Ƽ��� 
		if(bgm_times>=1320){
			bgm_times=0; //��l��bgm_times 
			sound_bgm.play(); //���s����bgm 
		}else{
			bgm_times++; //�O��+1 
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
		sound_bgm.play(); //bgm���ּ���
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
			            if(event.type == Event::TextEntered){  //��r��J�P�w 
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
					score = 0; //��l�Ƥ���
					bgm_times=0;
					g =  frame = 0.f; //��l�ƭ��q�B�V(�Ω�]�w�����ϥܻP�ɨ�)
					text_score.setString(to_string(score)); //��l�Ƥ��Ƥ�r���e 
					pipes.clear(); //�޹D�����M��
					bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //��l�Ƴ����y�� 
					gameover = false; //�]�����������_ 
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
					for(auto &p:pipes){ //�M���Ҧ��޹D 
						window->draw(p); //�ݰ�����ܺ޹D 
					}
					window->draw(*bird); //�ݰ�����ܳ�
					window->draw(text_score); //�ݰ�����ܤ��� 
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
			sbtn_start->setTextureRect(IntRect(btn_start.getSize().x/2.f,0,btn_start.getSize().x/2.f,btn_start.getSize().y)); //�令�ƹ��b�W�Ϥ� 
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _inputname;
			}
		}else{
			sbtn_start->setTextureRect(IntRect(0,0,btn_start.getSize().x/2.f,btn_start.getSize().y));
		}
	}
	void button_Rank(){
		if (isMouseOver(sbtn_introduce)){
			sbtn_introduce->setTextureRect(IntRect(btn_introduce.getSize().x/2.f,0,btn_introduce.getSize().x/2.f,btn_introduce.getSize().y)); //�令�ƹ��b�W�Ϥ�
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _introduce;
			}
		}else{
			sbtn_introduce->setTextureRect(IntRect(0,0,btn_introduce.getSize().x/2.f,btn_introduce.getSize().y));
		}
	}
	void button_Introduce(){
		if (isMouseOver(sbtn_showrank)){
			sbtn_showrank->setTextureRect(IntRect(btn_showrank.getSize().x/2.f,0,btn_showrank.getSize().x/2.f,btn_showrank.getSize().y)); //�令�ƹ��b�W�Ϥ� 
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
			sbtn_enter->setTextureRect(IntRect(btn_enter.getSize().x/2.f,0,btn_enter.getSize().x/2.f,btn_enter.getSize().y)); //�令�ƹ��b�W�Ϥ� 
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
			sbtn_restart->setTextureRect(IntRect(btn_restart.getSize().x/2.f,0,btn_restart.getSize().x/2.f,btn_restart.getSize().y)); //�令�ƹ��b�W�Ϥ�
			if (Mouse::isButtonPressed(Mouse::Left)){
				gamestatus = _game;
			}
		}else{
			sbtn_restart->setTextureRect(IntRect(0,0,btn_restart.getSize().x/2.f,btn_restart.getSize().y));
		}	
	}
	void button_Homepage(){
		if(isMouseOver(sbtn_homepage)){
			sbtn_homepage->setTextureRect(IntRect(btn_homepage.getSize().x/2.f,0,btn_homepage.getSize().x/2.f,btn_homepage.getSize().y)); //�令�ƹ��b�W�Ϥ� 
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
	FlappyBird(){ //�غc��(�l)�A�]�w��l�� 
	  setSFML(); //�ѩ�SFML�M�󪺪���]�w���i�b�غc�l����A�ҥH�t�~�I�s��� 
	}
	void flappy_start(){
		changeWindow();
	}
};
