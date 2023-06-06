#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "set_rank.h"
#include "testbox.hpp"
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
//�y���j�� ��u�@ �{���]�p �Ĥ��� �����M�� FlappyBird ���C���{���]�p  
using namespace std;
using namespace sf;
enum Status{_homepage, _inputname, _game, _gameover, _showrank, _introduce};//�C�����A��enum 
class FlappyBird : private setrank{ //FlappyBird�~��setrank
	private:
	Event event;//�ŧisf::�ƥ� event 
	float mouse_x,mouse_y,btn_x,btn_y,btn_w,btn_h;//�ŧi�ƹ�x,y��m	���sx,y��m ���s�e,�� 
	RenderWindow *window; //�ŧisf::RenderWindow �����ܼ� (�ʺA�O����) 
	float g,frame,interval; //�ŧi���O�B�V(�Ω�ʵe)�B���j(�޹D�����j) 
	int count,bgm_timing,rankfield,any_timing,now_rank;//�`��(���ޥͦ��ɾ�)�BBGM�ɾ�(�`������)�B�Ʀ�d��(��ܪ��d��)�B��L�ɾ�(�Ω�b�Y�P�ťի��U�ܬ����)�B�ثe�ƦW 
	string name,showrank,str; //�ŧi�W�١B��ܱƦ�]�Bstr�Ω�ͦ�sf::Text����PClass Button����ɨϥ� 
	long long score; //�ŧi���� 
	pair<int,long long> now; //�Ω�setrank��pair<int,long long> <�ثe�ƦW,���v�̰���> 
	SoundBuffer buffer_hit,buffer_wing,buffer_add,buffer_bgm,buffer_no1; //�ŧisf::SoundBuffer����Ω�Ū������ 
	Sound sound_hit,sound_wing,sound_add,sound_bgm,sound_no1; //�ŧisf::Sound���� ���ɪ����� 
	Font font; //�ŧisf::Font���� Ū���r�� 
	Text text_score,text_rank,text_introduce,text_announce,arrow_up,arrow_down,ann_space; //�ŧisf::Text ���� �Ω��r��� 
	Texture bg, bd, pipe,team;//�ŧisf::Texture ���� �Ω�[���Ϥ����z(����Ω�]�w���F�Ϥ�) 
	Sprite *background, *bird, *pipeBottom, *pipeTop,*team_picture;//�ŧi sf::Sprite �����ܼ�(�ʺA�O����) �Ω�Ϲ��B�Ϲ����ʡB�Ϲ��I��...
	vector<Sprite> pipes;//�ŧi vector<sf::Sprite> �}�C �Ω�s��B�R���޹D 
	bool gameover, addscore; //�ŧibool �C�������B�[�� 
	Status gamestatus = _homepage; //�ŧienum Status �Ω�P�_�C����e�B�檬�A 
	Textbox *textbox1; //�ŧi Class Textbox �����ܼ�(�ʺA�O����) 
	Button *button_play,*button_enter,*button_restart,*button_home,*button_rank,*button_intro; //�ŧi Class Button �����ܼ�(�ʺA�O����)  
	void _showRank(){//setrank���O������_��ܱƦ�](�W���B�W�١B����) 
		showrank="";//��ܤ���r 
		if(v.size()==0)//rank.txt�L��� 
			showrank="No Data";//���No Data 
		for(int i=rankfield;i<v.size();i++){//�M��vector v
			showrank+="NO."+to_string(renewrank(v[i]).first)+" "+v[i].first+" Score:"+to_string(v[i].second)+"\n";//��ܮ榡
			if(i==rankfield+6)//7�H�ɰ��U 
				break;//���Xfor�j�� 
		}
		text_rank.setString(showrank);//�]�w��r 
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,250-text_rank.getGlobalBounds().height/2.f);//�]�w��m 
	}
	void _gameOver(){ //�C�����������ġB���A�B��e�W����ܻP���v���Ƥ���� 
		sound_hit.play(); //����������
		gameover = true; //�C������ 
		gamestatus=_gameover; //���A�]�w 
		now = renewrank({name,score}); //���s���ƱƦ� 
		now_rank=now.first; //�ثe���Ʀ�  
		text_rank.setString("NO."+to_string(now_rank)+" "+name+" Score:"+to_string(score)+" History:"+to_string(now.second)); //��ܮ榡 
		text_rank.setPosition(500-text_rank.getGlobalBounds().width/2.f,187.5f);//�]�w��m 
		if(now.first==1 && score>=now.second){//�p�G�ثe�O�Ĥ@�W�B���Ƭ�}�ۤv�̰������A�Ȱ��I�����֡A����ӧQ���� 
			sound_bgm.stop();//�Ȱ��I������ 
			bgm_timing=1000;//�]�w�I�����֮ɶ��A�Ω�U���`�� 
			sound_no1.play();//����ӧQ���� 
		}		
	}
	void setSFML(){ //�Ω�]�w��l��
		//�ѼƳ]�w 
		name=""; //�M��name
		g = frame = 0.f;; //�w�]�������V�U�B�V(�Ω�]�w�����ϥܻP�ɨ�) 
		interval = 240.f; //�]�w�޹D�϶� 
		count = 0; //�`��-�Ω�ͦ��޹D
		bgm_timing = 0; //�]�w�I�����ּ��񤧥��O�� 
		gameover = addscore = false;  //�����B�[�����_ 
		score = 0;  //���Ƭ�0
		rankfield=0; //�ƦW��� ��l���Ĥ@�W�b�̤W�� 
		//�����]�w 
		window = new RenderWindow(VideoMode(1000, 600),TEAMNAME); //�����]�w 
		window->setPosition(Vector2i(0, 0)); //��l�Ƶ����y�Х��W��(0,0) 
		window->setKeyRepeatEnabled(true); //�i�H���U���s�A�|���ƧP�_ 
		//�ձ��C���t�� 
		window->setFramerateLimit( 60 ); //����̤j�V�ơA�ѩ󥦦b�����ϥ� sf::sleep�A���ר��M�󩳼h�ާ@�t�ΡA���G�]�i�঳�I����T�A
		//window->setFramerateLimit( 0 ); //�L�V�ƭ���A�C���H�̧֪��t�׶i�� 
		//textbox������ 
		textbox1 = new Textbox(40,Color::White,true);//�r��40�A�զr 
		/*�H�U�O�I�����ϻP���F�]�w*/
		if(!bg.loadFromFile(BACKGROUND))//���J�Ϥ�
			cout<<"Fail loading background.png"<<endl;//���� 
		background = new Sprite(); //�إߺ��F
		background -> setTexture(bg); //���F�Ϯ׳]���I����
		//�L���]�w��m�P�j�p ��l��m��(0,0) �����P�ϵ��j 
		
		/*�H�U�O�����ϻP���F�]�w*/
		if(!bd.loadFromFile(BIRD))//���J�Ϥ�
			cout<<"Fail loading bird.png"<<endl;  
		bird = new Sprite(); //�إߺ��F 
		setPictureSize(bird,&bd,2.5f,3,500,75);
		/*�ζ��Ӥ�*/
		if(!team.loadFromFile(TEAM_PICTURE))//���J�Ϥ�
			cout<<"Fail loading team_picture"<<endl;//����
		team_picture=new Sprite();//�إߺ��F
		team_picture->setTexture(team);//���F�Ϯ׳]���ζ��Ӥ� 
		team_picture->setScale(0.24,0.24);//�]�w���F(�Ϥ�)�j�p 
		team_picture->setPosition(500-team_picture->getGlobalBounds().width/2.f,350-team_picture->getGlobalBounds().height/2.f);//�]�w���F(�Ϥ�)��m 
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
		
		if(!font.loadFromFile(FONT))//���J�r�� 
			cout<<"Fail loading flappybird.ttf"<<endl; 
		
		/*�H�U�O�r��P��r�]�w*/ 
		str=to_string(score);
		setTextSFML(&text_score,10.f,10.f,50,str);//���Ʀr��P��r 
		str=""; 
		setTextSFML(&text_rank,10.f,250.f,50,str);//rank�r��P��r 
		str="This Flappy Bird game is created by B1143007 Lee Min-Chen, B114\n3009 Wu Bing-Rong, B1143015 Lin Xuan-You, B1143021 Lin Cheng-Wei\n, B1143027 ChenBo-Hao, and B1143036 Huang Qi-Ting, is a simple \nbut addictive game. Guide the bird through pipes by tapping the \nscreen or pressing spacebar. Avoid collisions with pipes and \nthe ground. Score points for each successful passage. \nChallenge yourself with increasing difficulty. Aim for the \nhighest score and compete with friends.";
		setTextSFML(&text_introduce,10.f,10.f,30,str);//���Цr��P��r 
		str="Name : \nWarning : Only supports input of English,\nnumbers and some symbols";
		setTextSFML(&text_announce,100.f,100.f,40,str);//���ܦW�ٿ�J�r��P��r 
		str="^";
		setTextSFML(&arrow_up,80.f,350.f,40,str);//�V�W�b�Y�r��P��r 
		setTextSFML(&arrow_down,80.f,425.f,40,str);//�V�U�b�Y�r��P��r 
		arrow_down.setScale(1.0f, -1.0f);//�V�U�b�Y�W�U��V 
		str="SPACE";
		setTextSFML(&ann_space,10.f,550.f,40,str);
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
				
		textbox1->setFont(font); //�]�w�r�� 
		textbox1->setPosition({240,100});  //textbox��m 
		textbox1->setLimit(true,15);  //�]�w�O�_�]��and�r�ƭ���
		/*Button���O���󤧴���*/
		str=BUTTON_Play; //str�]�����s�Ϥ���m 
		button_play=new Button(str,0.4f,500.f,250.f); //���splay����]�w(���z�B���F�B�j�p�B��m) 
		str=BUTTON_ENTER; //str�]�����s�Ϥ���m  
		button_enter=new Button(str,0.4f,500.f,375.f); //���senter����]�w(���z�B���F�B�j�p�B��m)  
		str=BUTTON_RESTART; //str�]�����s�Ϥ���m  
		button_restart=new Button(str,0.4f,500.f,375.f); //���srestart����]�w(���z�B���F�B�j�p�B��m)  
		str=BUTTON_SHOWRANK; //str�]�����s�Ϥ���m  
		button_rank=new Button(str,0.4f,500.f,375.f); //���srank����]�w(���z�B���F�B�j�p�B��m)  
		str=BUTTON_HOMEPAGE; //str�]�����s�Ϥ���m  
		button_home=new Button(str,0.4f,500.f,500.f); //���shome����]�w(���z�B���F�B�j�p�B��m)  
		str=BUTTON_INTRODUCE; //str�]�����s�Ϥ���m  
		button_intro=new Button(str,0.4f,500.f,500.f); //���sintro����]�w(���z�B���F�B�j�p�B��m)  
		changeWindow(); //�I�s�������ܨ�� 
	}
	void setTextSFML(Text *text_show,float px,float py,int size,string str){//�]�wText���榡�P��r���e 
		text_show->setFont(font); //�M�Φr�� 
		text_show->setString(str); //��r���e�]�w  
		text_show->setPosition(px, py); //��m�]�w
		text_show->setCharacterSize(size); //�r��j�p�]�w
		text_show->setOutlineThickness(3); //�r��ʲӳ]�w
	}	
	void setPictureSize(Sprite *spt,Texture *txt,float resize,float cut,float px,float py){//�]�w���F���Ϥ��B�j�p�B��m 
		spt->setTexture(*txt);//�Ϥ��]�w 
		spt->setScale(resize,resize);//�j�p(���) 
		spt->setTextureRect(IntRect(0,0,txt->getSize().x/cut,txt->getSize().y));//���Ϥ��S�w�d�� 
		spt->setPosition(px-spt->getGlobalBounds().width/2.f,py-spt->getGlobalBounds().height/2.f);//�]�w��m 
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
		window->draw(ann_space); 
		window->display(); //�I�sOpenGL��V������ե�(���e�V���Ҧ�����ܹϹ���ܦb�e���W) 
	}
	void pipeMove(){ //�Ω󲾰ʤ��ޡA�P�������D 
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
				_gameOver();//�I�s�C����������� 
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
		if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //����25�T��W
			any_timing =0;//�q0�ƭn��ժ��ɾ� 
			ann_space.setColor(Color::Red);//��Space��� 
			sound_wing.play(); //���񴧯ͻH���� 
			bird->setRotation(-frame*2 - 10.f); //����y�L�V�W�� 
			g = -8.f; //�]�w���q�V�U 
		}
		else
			bird->setRotation(frame*2 - 10.f); //����y�L�V�U��
		if(any_timing>=10){
			ann_space.setColor(Color::White); //��Space��� 
		}else{
			any_timing++;//��իe���˼� 
		}
		bird->move(0, g); //�V�U�Y�� 
		g += 0.5f; //�v���W�� 
		if(bird->getPosition().y>650){ //���ӳ��W�X�e��(y>650) 
			_gameOver(); //�I�s�C�����Ѥ���� 
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
			bgmCircle(); //bgm�`�� 
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
		if(bird->getPosition().y>90) //���ּ���Play���s���e�n���U�� 
			g-=0.05f; //�v����t�A�̫�W�� 
		else if(bird->getPosition().y<50) //���ּ�������������e�n���U�� 
			g+=0.05f; //�v����t�A�̫�U�� 
	}
	void bgmCircle(){ //bgm���� 
		if(bgm_timing>=1320){ //�`���ɾ� 
			bgm_timing=0; //��l��bgm_timing 
			sound_bgm.play(); //���s����bgm 
		}else{
			bgm_timing++; //�O��+1 
		}
	}
	void changeWindow(){ //���ܵ�������� 
		sound_bgm.play(); //bgm���ּ���
		while( window->isOpen() ){ //��window�}�Ҫ��A 
			bgmCircle(); //�I�s�I�����ִ`����� 
			window->clear(); //�M�ŵe���A�M���W�@�V�����e 
			window->draw(*background); //�w��V�I�� 
			switch(gamestatus){ //�C�����A���P�_�P���椣�P�ʧ@ 
				case _homepage: //��b������ 
					while(window->pollEvent(event)){ //���������ƥ� 
						if (event.type == sf::Event::Closed) //�����Q���U����(x) 
			                window->close(); //��������
			            if(button_play->button_Mouse(*window)){//�Yplay���s�Q���U 
							button_Play(); //����Play�ʧ@ 
						}
						if(button_rank->button_Mouse(*window)){//�Yrank���s�Q���U
							button_Rank(); //����Rank�ʧ@
						}
						if(button_intro->button_Mouse(*window)){//�Yintro���s�Q���U
							button_Introduce(); //����Introduce�ʧ@
						}
					}
					home_BirdAnime(); //�I�s���������ʵe 
					window->draw(*button_play->sbtn); //�w��Vplay���s 
					window->draw(*button_rank->sbtn); //�w��Vrank���s 
					window->draw(*button_intro->sbtn); //�w��Vintroduce���s 
					window->draw(*bird); //�w��Vbird���s 
					window->display(); //�����V 
					break;
				case _inputname:
					while(window->pollEvent(event)){ //���������ƥ� 
						if(event.type == Event::Closed) //�����Q���U����(x)
			                window->close(); //��������
			            if(event.type == Event::TextEntered){  //��r��J�P�w 
			            	textbox1->typedOn(event); //�I�stextbox���� 
						}
						if(button_home->button_Mouse(*window)){ //�Yhome���s�Q���U
							button_Homepage(); //����Homepage�ʧ@
						} 
						if(button_enter->button_Mouse(*window)){ //�Yenter���s�Q���U
							button_Enter(); //����Enter�ʧ@
						} 
					}
					window->draw(*button_home->sbtn); //�w��Vhome���s
					window->draw(*button_enter->sbtn); //�w��Venter���s 
					window->draw(text_announce); //�w��Vtext announce 
					textbox1->drawTo(*window); //�w��Vtextbox1 
					window->display(); //�����V 
					break;
				case _game:
					score = 0; //��l�Ƥ���
					bgm_timing=0; //��l�ƭI�����ִ`���ɾ� 
					g =  frame = 0.f; //��l�ƭ��q�B�V(�Ω�]�w�����ϥܻP�ɨ�)
					text_score.setString(to_string(score)); //��l�Ƥ��Ƥ�r���e 
					pipes.clear(); //�޹D�����M��
					bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //��l�Ƴ����y�� 
					gameover = false; //�]�����������_ 
					reset_Bird();//���]�����Ϥ� 
					run(); //����C�� 
					break; 
				case _gameover:
					while(window->pollEvent(event)){ //���������ƥ�  
						if(event.type == sf::Event::Closed) //�����Q���U����(x)
			                window->close(); //��������
			            if(button_restart->button_Mouse(*window)){ //�Yrestart���s�Q���U
							button_Restart(); //����Restart�ʧ@
						}
						if(button_home->button_Mouse(*window)){ //�Yhome���s�Q���U
							button_Homepage(); //����Homepage�ʧ@
						} 
					}	
					for(auto &p:pipes){ //�M���Ҧ��޹D 
						window->draw(p); //�ݰ�����ܺ޹D 
					}
					window->draw(*bird); //�w��V��
					window->draw(text_score); //�w��V���� 
					window->draw(*button_restart->sbtn);  //�w��Vrestart���s
					window->draw(*button_home->sbtn); //�w��Vhome���s
					window->draw(text_rank); //�w��V�ثe�Ʀ�P���v�̰� 
					window->display(); //�����V 
					break;
				case _showrank:
					_showRank();//��ܱƦ椧��� 
					while(window->pollEvent(event)){ //���������ƥ�  
						if(event.type == sf::Event::Closed) //�����Q���U����(x) 
			                window->close(); //��������
			            if(Keyboard::isKeyPressed(Keyboard::Up)){//�ק�W�b�Y�C��-�� 
			            	any_timing=0;//�]�w�ɶ� 
			            	arrow_up.setColor(Color::Red);//�W�b�Y�令�� 
							if(rankfield>0)//��ܱƦW�̰��O�Ĥ@�W 
								rankfield--;//��ܱƦW���W 
						}
			            if(Keyboard::isKeyPressed(Keyboard::Down)){//�ק�U�b�Y�C��-�� 
			            	any_timing=0;
			            	arrow_down.setColor(Color::Red);//�U�b�Y�令�� 
							if(rankfield<v.size()-1)//��ܱƦW�̧C�̫�@�W
								rankfield++;//��ܱƦW���U
						}
						if(button_home->button_Mouse(*window)){ //�Yhome���s�Q���U
							button_Homepage(); //����Homepage�ʧ@
						}
					}
					
					if(any_timing>=10){//��g�L10��switch�b�Y�令�� 
						arrow_up.setColor(Color::White); //�ק�W�b�Y�C��-�� 
						arrow_down.setColor(Color::White);//�ק�U�b�Y�C��-�� 
					}else{
						any_timing++;
					}
					window->draw(arrow_up);//�w��V�V�W�b�Y 
					window->draw(arrow_down);//�w��V�V�U�b�Y 
					window->draw(text_rank); //�w��V�Ʀ�] 
					window->draw(*button_home->sbtn); //�w��Vhome���s 
					window->display(); //�����V 
					break;
				case _introduce:
					while(window->pollEvent(event)){ //���������ƥ�
						if(event.type == sf::Event::Closed) //�����Q���U����(x) 
			                window->close();//��������
						if(button_home->button_Mouse(*window)){ //�Yhome���s�Q���U
							button_Homepage(); //����Homepage�ʧ@
						}
					}
					window->draw(*team_picture); //�w��V�p�շӤ� 
					window->draw(*button_home->sbtn); //�w��Vhome���s 
					window->draw(text_introduce);  //�w��V���� text 
					window->display(); //�����V
					break;
				dafault: //default �z�פW�C�����A�S���ҥ~ 
					gamestatus = _homepage; //�p�G�o�ͨҥ~�A���ܭ��� 
					break;
			}
		}
	}
	
	void button_Play(){ //Play���s���U���ʧ@���
		gamestatus = _inputname; //�i�J��J�W�� 
	}
	void button_Rank(){ //Rank���s���U���ʧ@��� 
		gamestatus = _showrank; //�i�J�Ʀ�] 
	}
	void button_Introduce(){ //Introduce���s���U���ʧ@���
		gamestatus = _introduce; //�i�J���� 
	}
	
	void button_Enter(){ //Enter���s���U���ʧ@���
		name=textbox1->getText();//name�]�w��textbox1�����e	
		sound_bgm.play(); //bgm���� 
		gamestatus = _game; //�i�J�C�� 
	}
	void button_Restart(){ //Restart���s���U���ʧ@���
		sound_bgm.play(); //bgm����
		gamestatus = _game; //�i�J�C�� 
	}
	void button_Homepage(){ //Homepage���s���U���ʧ@��� 
		sound_bgm.play(); //bgm����
		bgm_timing=0; //���sbgm�j��ɾ� 
		gamestatus = _homepage; //�i�J���� 
		g =  frame = 0.f; //�w�]�������V�U�B�V(�Ω�]�w�����ϥܻP�ɨ�) 
		setPictureSize(bird,&bd,2.5f,3,500,75); //�]�w�����Ϥ��B�j�p�P��m 
		bird->setRotation(0); //�]�w�����ਤ 
	}
	public:
	FlappyBird(){ //�غc��(�l)�A�]�w��l�� 
	  setSFML(); //�ѩ�SFML�M�󪺪���]�w���i�b�غc�l����A�ҥH�t�~�I�s��� 
	}
};
